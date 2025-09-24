package org.love2d.android.util

import android.content.Context
import android.content.Intent
import android.net.Uri
import android.os.Build
import android.provider.Settings
import com.google.accompanist.permissions.ExperimentalPermissionsApi
import com.google.accompanist.permissions.PermissionState
import com.google.accompanist.permissions.isGranted
import com.google.accompanist.permissions.shouldShowRationale

/**
 * ClassName PermissionUtil
 * Description
 * Create by hjr
 * Date 2025/6/20 13:49
 */
object PermissionUtil {

    val MANAGE_EXTERNAL_STORAGE = listOf(android.Manifest.permission.MANAGE_EXTERNAL_STORAGE)
    val READ_AND_WRITE_EXTERNAL_STORAGE = listOf(
        android.Manifest.permission.READ_EXTERNAL_STORAGE,
        android.Manifest.permission.WRITE_EXTERNAL_STORAGE
    )

    val STORAGE_PERMISSIONS = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
        // Android 11+ 走 MANAGE_EXTERNAL_STORAGE 授权跳转
        MANAGE_EXTERNAL_STORAGE
    } else {
        // Android 10及以下，动态申请 WRITE_EXTERNAL_STORAGE
        READ_AND_WRITE_EXTERNAL_STORAGE
    }



    /**
     * 判断是否为永久拒绝：权限未授权，且 shouldShowRationale == false
     */
    @OptIn(ExperimentalPermissionsApi::class)
    fun isPermanentlyDenied(permissionState: PermissionState): Boolean {
        return !permissionState.status.isGranted &&
                !permissionState.status.shouldShowRationale
    }

    /**
     * 跳转到系统设置 -> 当前 App 的详情页
     */
    fun openAppSettings(context: Context) {
        val intent =
            Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS).apply {
                data = Uri.parse("package:${context.packageName}")
                flags = Intent.FLAG_ACTIVITY_NEW_TASK
            }
        context.startActivity(intent)
    }
}