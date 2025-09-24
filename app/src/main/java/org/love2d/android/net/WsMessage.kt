package org.love2d.android.net

import com.squareup.moshi.JsonClass

/**
 * ClassName WsMessage
 * Description
 * Create by hjr
 * Date 2025/7/9 17:14
 */
@JsonClass(generateAdapter = true)
data class WsMessage(
    val type : String,
    val payload : String
)