package org.love2d.android.net

import com.squareup.moshi.JsonClass
import org.love2d.android.net.bean.ModListItemBean

@JsonClass(generateAdapter = true)
data class ApiResponse<T>(
    val code: Int,
    val message: String,
    val data: T
)

// 专门用于解析 Mod 列表响应的完整数据类
@JsonClass(generateAdapter = true)
data class PageListApiResponse<T>(
    val code: Int,
    val message: String,
    val data: List<T>,
    val page: Int,
    val totalPages: Int
)
