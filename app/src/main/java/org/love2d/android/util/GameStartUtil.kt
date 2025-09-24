package org.love2d.android.util

import android.app.ActivityManager
import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.content.IntentFilter
import android.os.Build
import android.os.Handler
import android.os.Looper
import android.os.Process
import android.util.Log
import androidx.core.content.ContextCompat
import kotlinx.coroutines.flow.MutableStateFlow
import org.love2d.android.GameActivity
import org.love2d.android.GameLoadingActivity
import org.love2d.android.room.game.GameInfo

object GameStartUtil {

    var currentRunningGame = MutableStateFlow<Pair<Boolean, GameInfo>?>(null)

    // 关键步骤1：定义清晰、唯一的广播Action字符串
    // 用于命令游戏进程关闭
    const val ACTION_REQUEST_SHUTDOWN = "org.love2d.android.ACTION_REQUEST_SHUTDOWN"
    // 用于接收游戏进程已确认关闭的回信
    const val ACTION_SHUTDOWN_CONFIRMED = "org.love2d.android.ACTION_SHUTDOWN_CONFIRMED"

    /**
     * 新的方法：先发送关闭命令，等待确认后再安全地启动新游戏。
     * 用这个方法替代 killAndStartGame。
     */
    fun shutdownAndRestartGame(context: Context, game: GameInfo) {
        // 首先检查游戏进程是否真的在运行
        if (!isGameProcessRunning(context)) {
            Log.d("GameStartUtil", "游戏进程未运行，直接启动。")
            startGame(context, game)
            return
        }

        Log.d("GameStartUtil", "游戏进程正在运行，开始执行优雅关闭流程...")

        // 关键步骤2：注册一个一次性的广播接收器，用于接收“已关闭”的确认回信
        val shutdownConfirmationReceiver = object : BroadcastReceiver() {
            override fun onReceive(ctx: Context?, intent: Intent?) {
                if (intent?.action == ACTION_SHUTDOWN_CONFIRMED) {
                    Log.d("GameStartUtil", "✅ 收到游戏进程已关闭的确认回信，现在可以安全启动新游戏了。")

                    currentRunningGame.value = null
                    // 注销自己，避免内存泄漏
                    context.unregisterReceiver(this)

                    // 在这里，我们100%确定旧进程已处理完退出逻辑
                    // 为保险起见，再延迟一小段时间（例如500ms），给操作系统充分的回收时间
                    Handler(Looper.getMainLooper()).postDelayed({
                        startGame(context, game)
                    }, 500)
                }
            }
        }

        // 注册这个接收器
        val intentFilter = IntentFilter(ACTION_SHUTDOWN_CONFIRMED)
        // 兼容 Android 14 (API 34) 及以上版本
        val receiverFlags = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            ContextCompat.RECEIVER_EXPORTED
        } else {
            0
        }
        ContextCompat.registerReceiver(context, shutdownConfirmationReceiver, intentFilter, receiverFlags)


        // 关键步骤3：发送“请关闭”的命令广播给游戏进程
        Log.d("GameStartUtil", "即将发送广播, Action: $ACTION_REQUEST_SHUTDOWN, 包名: ${context.packageName}")
        val requestIntent = Intent(ACTION_REQUEST_SHUTDOWN)
        requestIntent.setPackage(context.packageName) // <--- 【重要】添加这一行
        context.sendBroadcast(requestIntent)
    }


    fun startGame(context: Context, game: GameInfo, isKill: Boolean = false, running: (GameInfo) -> Unit = {}) {
        if (isGameProcessRunning(context)) {
            //发送一个弹窗出去，询问用户是否要关闭当前游戏进程
            running(game)
        } else {
            if (isKill) killGameProcess(context)
            startGame(context, game)
        }
    }

    fun killAndStartGame(context: Context, game: GameInfo) {
        killGameProcess(context)
        Log.e("HJR-Game", "killAndStartGame $game")
        startGame(context, game)
    }

    fun killGameProcess(context: Context) {
        val running = isGameProcessRunning(context)
        Log.e("HJR", "游戏进程是否正在运行：$running")
        if (!running) {
            currentRunningGame.value = null
            return
        }
        // 关键步骤2：注册一个一次性的广播接收器，用于接收“已关闭”的确认回信
        val shutdownConfirmationReceiver = object : BroadcastReceiver() {
            override fun onReceive(ctx: Context?, intent: Intent?) {
                if (intent?.action == ACTION_SHUTDOWN_CONFIRMED) {
                    Log.d("GameStartUtil", "✅ 收到游戏进程已关闭的确认回信，现在可以安全启动新游戏了。")
                    currentRunningGame.value = null
                    // 注销自己，避免内存泄漏
                    context.unregisterReceiver(this)
                }
            }
        }
        // 注册这个接收器
        val intentFilter = IntentFilter(ACTION_SHUTDOWN_CONFIRMED)
        // 兼容 Android 14 (API 34) 及以上版本
        val receiverFlags = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            ContextCompat.RECEIVER_EXPORTED
        } else {
            0
        }
        ContextCompat.registerReceiver(context, shutdownConfirmationReceiver, intentFilter, receiverFlags)
        // 关键步骤3：发送“请关闭”的命令广播给游戏进程
        Log.d("GameStartUtil", "即将发送广播, Action: $ACTION_REQUEST_SHUTDOWN, 包名: ${context.packageName}")
        val requestIntent = Intent(ACTION_REQUEST_SHUTDOWN)
        requestIntent.setPackage(context.packageName) // <--- 【重要】添加这一行
        context.sendBroadcast(requestIntent)
    }

    private fun isGameProcessRunning(context: Context): Boolean {
        val am = context.getSystemService(Context.ACTIVITY_SERVICE) as ActivityManager
        val packageName = context.packageName
        return am.runningAppProcesses.any {
            it.processName == "$packageName:game_process"
                    && currentRunningGame.value != null
                    && currentRunningGame.value?.first == true
        }
    }

    //回到游戏
    fun bringGameToFront(context: Context) {
        val intent = Intent(context, GameActivity::class.java).apply {
            flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_REORDER_TO_FRONT
        }
        context.startActivity(intent)
    }

    private fun startGame(context: Context, game: GameInfo) {
        Log.e("HJR-Game", "startGame $game")
        Handler(Looper.getMainLooper()).postDelayed({
            val intent = Intent(context, GameLoadingActivity::class.java)
            if (!game.filePath.isNullOrEmpty()) {
                intent.putExtra("gamePath", game.filePath)
            }
            if (game.isEnableMod) {
                Log.e("HJR-Game", "modPath ${game.modPath}")
                intent.putExtra("modPath", game.modPath)
            }
            if (game.savePath.isNotBlank()) {
                intent.putExtra("savePath", game.savePath)
            }
            currentRunningGame.value = Pair(true, game)
            context.startActivity(intent)
        }, 500) // 稍微延迟一下，确保进程干净结束
    }

    fun getGameProcessPid(context: Context): Int? {
        val am = context.getSystemService(Context.ACTIVITY_SERVICE) as ActivityManager
        val processName = "${context.packageName}:game_process"
        val processList = am.runningAppProcesses ?: return null

        for (proc in processList) {
            if (proc.processName == processName) {
                return proc.pid
            }
        }
        return null // 没找到
    }

    fun kill(context: Context) {
        val pid = getGameProcessPid(context)
        if (pid != null && pid > 0) {
            Process.killProcess(pid)
            currentRunningGame.value = null
        }
    }
}