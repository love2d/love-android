package org.love2d.android.util

import android.view.KeyEvent
import org.libsdl.app.SDLActivity

object KeyboardUtil {
    fun simulateKey(keyCode: Int, isSendUp: Boolean = true, isSendDown: Boolean = true) {
        val down = KeyEvent(KeyEvent.ACTION_DOWN, keyCode)
        val up = KeyEvent(KeyEvent.ACTION_UP, keyCode)

        SDLActivity.getContentView()?.requestFocus() // 确保 SDL 有焦点

        if (isSendDown) {
            SDLActivity.handleKeyEvent(null, down.keyCode, down, null)
        }
        if (isSendUp) {
            SDLActivity.handleKeyEvent(null, up.keyCode, up, null)
        }
    }
}