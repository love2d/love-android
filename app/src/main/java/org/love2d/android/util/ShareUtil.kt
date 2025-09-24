package org.love2d.android.util

import android.content.Context
import android.content.Intent
import android.os.StrictMode
import android.os.StrictMode.VmPolicy
import androidx.core.content.FileProvider
import java.io.File


/**
 * ClassName ShareUtil
 * Description
 * Create by hjr
 * Date 2025/7/1 14:54
 */
object ShareUtil {

    fun shareFile(context: Context, path: String) {
        if (path.isEmpty()) return

        val file = File(path)
        if (!file.exists()) return

        val uri = FileProvider.getUriForFile(
            context,
            "${context.packageName}.fileprovider",
            file
        )

        val intent = Intent(Intent.ACTION_SEND).apply {
            type = "*/*"
            putExtra(Intent.EXTRA_STREAM, uri)
            flags = Intent.FLAG_GRANT_READ_URI_PERMISSION or Intent.FLAG_ACTIVITY_NEW_TASK
        }

        context.startActivity(Intent.createChooser(intent, "分享文件"))
    }


    /**
     * 分享前必须执行本代码，主要用于兼容SDK18以上的系统
     */
    private fun checkFileUriExposure() {
        val builder = VmPolicy.Builder()
        StrictMode.setVmPolicy(builder.build())
        builder.detectFileUriExposure()
    }
}