package org.love2d.android.util

// MMKVHelper.kt

import android.content.Context
import com.tencent.mmkv.MMKV

object MMKVHelper {

    private const val DEFAULT_ID = "default"

    fun init(context: Context) {
        MMKV.initialize(context)
    }

    private val defaultMMKV: MMKV
        get() = MMKV.mmkvWithID(DEFAULT_ID, MMKV.MULTI_PROCESS_MODE)

    // 存储
    fun putString(key: String, value: String) = defaultMMKV.encode(key, value)
    fun putInt(key: String, value: Int) = defaultMMKV.encode(key, value)
    fun putBoolean(key: String, value: Boolean) = defaultMMKV.encode(key, value)
    fun putLong(key: String, value: Long) = defaultMMKV.encode(key, value)
    fun putFloat(key: String, value: Float) = defaultMMKV.encode(key, value)

    // 获取
    fun getString(key: String, default: String = ""): String = defaultMMKV.decodeString(key, default) ?: default
    fun getInt(key: String, default: Int = 0): Int = defaultMMKV.decodeInt(key, default)
    fun getBoolean(key: String, default: Boolean = false): Boolean = defaultMMKV.decodeBool(key, default)
    fun getLong(key: String, default: Long = 0L): Long = defaultMMKV.decodeLong(key, default)
    fun getFloat(key: String, default: Float = 0f): Float = defaultMMKV.decodeFloat(key, default)

    // 删除
    fun remove(key: String) = defaultMMKV.removeValueForKey(key)
    fun clearAll() = defaultMMKV.clearAll()
}
