package org.love2d.android.bean

import android.os.Parcelable
import com.squareup.moshi.JsonClass
import kotlinx.parcelize.Parcelize

/**
 * ClassName SearchRequest
 * Description
 * Create by hjr
 * Date 2025/7/2 17:58
 */
@Parcelize
@JsonClass(generateAdapter = true)
data class SearchRequest(
    var name: String = "",
    var page: Int = 1,
    val limit: Int = 20,
) : Parcelable