package org.love2d.android.util

import java.io.File
import java.io.IOException

/**
 * ClassName ModPackageCreateUtil
 * Description
 * Create by hjr
 * Date 2025/7/1 16:40
 */
object ModPackageCreateUtil {
    fun copyDirectory(source: File, target: File) {
        if (!source.exists()) return
        try {
            if (source.isDirectory) {
                if (!target.exists()) {
                    target.mkdirs()
                }
                source.listFiles()?.forEach { child ->
                    copyDirectory(child, File(target, child.name))
                }
            } else {
                source.copyTo(target, overwrite = true)
            }
        } catch (e: IOException) {
            e.printStackTrace()
        }
    }
}