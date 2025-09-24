package org.love2d.android.util

import java.util.Locale

/**
 * ClassName TimeUtil
 * Description
 * Create by hjr
 * Date 2025/6/24 15:03
 */
object TimeUtil {

    //时间戳转YYYY-MM-DD HH:mm:ss
    fun timestampToTime(timestamp: Long?): String {
        if (timestamp == null || timestamp == 0L) return "暂无"
        try {
            val time = java.util.Date(timestamp)
            val format = java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.getDefault())
            return format.format(time)
        } catch (e: Exception) {
            return "暂无"
        }
    }
}