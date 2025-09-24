package org.love2d.android.bean

import android.os.Parcelable
import com.squareup.moshi.JsonClass
import kotlinx.parcelize.Parcelize

/**
 * ClassName CreateModDispositionBean
 * Description
 * Create by hjr
 * Date 2025/7/1 16:37
 */
@Parcelize
@JsonClass(generateAdapter = true)
data class CreateModDispositionBean(
    var isSetting: Boolean = false,
    var packageName: String = "",
    var isCreatePackage: Boolean = true,
) : Parcelable
