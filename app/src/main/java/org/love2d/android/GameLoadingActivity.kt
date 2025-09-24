package org.love2d.android

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import org.love2d.android.LoveApplication.Companion.appContext
import java.io.File

/**
 * ClassName GameLoadingActivity
 * Description
 * Create by hjr
 * Date 2025/8/19 10:35
 */
class GameLoadingActivity : AppCompatActivity() {

    private val filePath by lazy { intent.getStringExtra("gamePath") }
    private val modPath by lazy { intent.getStringExtra("modPath") }
    private val savePath by lazy { intent.getStringExtra("savePath") }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        initGameEnv()
        //延迟500ms
        startGame()
    }

    private fun startGame() {
        if (filePath.isNullOrEmpty()) return
        val intent = Intent(this, GameActivity::class.java).apply {
            flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
            data = Uri.fromFile(File(filePath!!))
        }
        intent.putExtra("savePath", savePath)
        intent.putExtra("modPath", modPath)
        Log.e("HJR", "startGame")
        startActivity(intent)
        finish()
    }

    private fun initGameEnv() {
        val absolutePath = File(appContext.getExternalFilesDir(null), "mods").absolutePath
        LoveApplication.setModPath(modPath ?: absolutePath)
    }
}