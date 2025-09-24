package org.love2d.android.util

import android.util.Log
import com.squareup.moshi.Moshi
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.launch
import okhttp3.OkHttpClient
import okhttp3.Request
import okhttp3.Response
import okhttp3.WebSocket
import okhttp3.WebSocketListener
import org.json.JSONObject
import org.love2d.android.LoveApplication
import org.love2d.android.net.WsMessage

/**
 * ClassName WebSocketManager
 * Description
 * Create by hjr
 * Date 2025/7/9 15:36
 */
object WebSocketManager {
    private var webSocket: WebSocket? = null
    private var isConnecting = false
    private var currentStatus = "未连接"
    private val jsonAdapter by lazy {
        val build = Moshi.Builder().build()
        val jsonAdapter = build.adapter(WsMessage::class.java)
        jsonAdapter
    }

    fun connect(
        url: String,
        onStatusUpdate: (String) -> Unit,
    ) {
        // 避免重复连接
        if (isConnecting || webSocket != null) {
            onStatusUpdate("已连接")
            currentStatus = "已连接"
            return
        }

        isConnecting = true

        val client = OkHttpClient()
        val request = Request.Builder().url(url).build()
        val listener = object : WebSocketListener() {
            override fun onOpen(ws: WebSocket, response: Response) {
                webSocket = ws
                onStatusUpdate("已连接")
                currentStatus = "已连接"
                sendPing()
            }

            override fun onMessage(ws: WebSocket, text: String) {
                //showLog("收到消息 $text")

                messageHandler(text)
            }

            override fun onFailure(ws: WebSocket, t: Throwable, response: Response?) {
                onStatusUpdate("连接失败：${t.localizedMessage}")
                currentStatus = "连接失败：${t.localizedMessage}"
                isConnecting = false
                webSocket = null
            }

            override fun onClosing(ws: WebSocket, code: Int, reason: String) {
                onStatusUpdate("连接关闭：$reason")
                currentStatus = "连接关闭：$reason"
                isConnecting = false
                webSocket = null
            }
        }

        client.newWebSocket(request, listener)
        // 不要立即 shutdown，这会关闭线程池影响后续连接
        // client.dispatcher.executorService.shutdown() ❌ 移除
    }

    fun messageHandler(message: String) {
        val wsMessage = jsonAdapter.fromJson(message)
        when (wsMessage?.type) {
            "pong" -> {
                //客户端心跳 移动端回复
                CoroutineScope(Dispatchers.Default).launch {
                    delay(2500)
                    sendPing()
                }
            }

            "synced" -> {
                FileSelectorUtil.base64ToZip(LoveApplication.appContext, wsMessage.payload)
            }
        }
    }

    fun disconnect(disconnect: () -> Unit) {
        if (webSocket != null) {
            webSocket?.close(1000, "客户端主动关闭")
            webSocket = null
            isConnecting = false
            disconnect()
        }
    }

    private fun sendPing() {
        if (webSocket != null) {
            val message = JSONObject()
            message.put("type", "ping")
            message.put("payload", System.currentTimeMillis().toString())
            webSocket?.send(message.toString())
        }
    }

    fun sendSync() {
        if (webSocket != null) {
            val message = JSONObject()
            message.put("type", "sync")
            message.put("payload", System.currentTimeMillis().toString())
            webSocket?.send(message.toString())
        }
    }

    fun isConnected(): Boolean = webSocket != null

    fun getCurrentStatus(): String = currentStatus

    private fun showLog(message: Any) {
        Log.e("HJR-WebSocket", message.toString())
    }
}
