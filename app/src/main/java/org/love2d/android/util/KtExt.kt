package org.love2d.android.util

import android.content.Context
import android.content.Intent
import android.net.Uri
import androidx.core.net.toUri
import com.squareup.moshi.Moshi
import com.squareup.moshi.kotlin.reflect.KotlinJsonAdapterFactory
import okhttp3.MediaType.Companion.toMediaType
import okhttp3.RequestBody
import okhttp3.RequestBody.Companion.toRequestBody

/**
 * ClassName KtExt
 * Description
 * Create by hjr
 * Date 2025/7/2 18:01
 */
inline fun <reified T> T.toJsonRequestBodyMoshi(
    tag: String = "JsonBody",
    moshi: Moshi = Moshi.Builder()
        .add(KotlinJsonAdapterFactory()) // 支持 Kotlin 数据类
        .build()
): RequestBody {
    val adapter = moshi.adapter(T::class.java)
    val json = adapter.toJson(this)
    return json.toRequestBody("application/json; charset=utf-8".toMediaType())
}

inline fun <reified T> T.toJson(
    moshi: Moshi = Moshi.Builder()
        .add(KotlinJsonAdapterFactory())
        .build()
): String {
    return moshi.adapter(T::class.java).toJson(this)
}

fun Context.startNetUri(url : String) {
    val uri = url.toUri()
    startActivity(Intent(Intent.ACTION_VIEW, uri).apply { flags = Intent.FLAG_ACTIVITY_NEW_TASK })
}