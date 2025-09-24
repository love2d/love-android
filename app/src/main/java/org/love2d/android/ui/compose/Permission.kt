package org.love2d.android.ui.compose

import android.content.Context
import android.content.Intent
import android.net.Uri
import android.os.Build
import android.os.Environment
import android.provider.Settings
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TextButton
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.window.Dialog
import androidx.core.net.toUri
import com.google.accompanist.permissions.ExperimentalPermissionsApi
import com.google.accompanist.permissions.rememberMultiplePermissionsState

/**
 * 权限请求的统一入口。
 * 它会根据权限类型自动选择合适的处理方式。
 *
 * @param permissions 需要请求的权限列表。
 * @param onPermissionGranted 所有权限都被授予时的回调。
 * @param onPermissionDenied 任何权限被拒绝时的回调。
 */
@Composable
fun PermissionGate(
    permissions: List<String>,
    onPermissionGranted: () -> Unit,
    onPermissionDenied: () -> Unit,
    onDismiss: () -> Unit
) {
    // 判断是否是请求 Android 11+ 的特殊文件权限
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R &&
        permissions.contains(android.Manifest.permission.MANAGE_EXTERNAL_STORAGE)
    ) {
        // 使用专门的处理器来处理所有文件访问权限
        ManageStoragePermissionHandler(
            onPermissionGranted = onPermissionGranted,
            onPermissionDenied = onPermissionDenied
        )
    } else {
        // 对于其他所有普通权限，使用 accompanist-permissions 库处理
        StandardPermissionHandler(
            permissions = permissions,
            onPermissionGranted = onPermissionGranted,
            onPermissionDenied = onPermissionDenied
        )
    }
}

/**
 * 专门处理 Android 11 (API 30) 及以上版本的所有文件访问权限 (MANAGE_EXTERNAL_STORAGE)。
 * 这种特殊权限必须通过跳转到系统设置页面手动授予。
 */
@Composable
private fun ManageStoragePermissionHandler(
    onPermissionGranted: () -> Unit,
    onPermissionDenied: () -> Unit
) {
    val context = LocalContext.current
    var showPermissionDialog by remember { mutableStateOf(false) }

    // 准备一个 ActivityResultLauncher，用于接收从设置页面返回的结果
    val launcher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.StartActivityForResult()
    ) {
        // 当从设置页面返回时，再次检查权限是否已被授予
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
            if (Environment.isExternalStorageManager()) {
                onPermissionGranted()
            } else {
                onPermissionDenied()
            }
        }
    }

    // 检查当前是否已拥有权限
    val hasPermission = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.R) {
        Environment.isExternalStorageManager()
    } else {
        true // Android 11 以下的版本此逻辑不适用，视为已有权限
    }

    if (hasPermission) {
        // 如果已经有权限，直接执行成功回调
        onPermissionGranted()
    } else {
        // 如果没有权限，只在首次进入时触发一次，将状态设为需要显示对话框
        LaunchedEffect(Unit) {
            showPermissionDialog = true
        }
    }

    // 根据状态决定是否显示请求对话框
    if (showPermissionDialog) {
        PermissionDialog(
            title = "需要权限",
            message = "为了让应用程序正常运作，需要您授予所有文件的访问权限。",
            confirmText = "前往授权",
            onConfirm = {
                // **核心修正**：将跳转逻辑放在按钮的 onClick 事件中
                // 这样可以确保每次点击都会触发跳转
                val intent = Intent(Settings.ACTION_MANAGE_APP_ALL_FILES_ACCESS_PERMISSION).apply {
                    data = ("package:" + context.packageName).toUri()
                }
                launcher.launch(intent)
                showPermissionDialog = false // 点击后可以先关闭对话框
            },
            onDismiss = {
                showPermissionDialog = false
                onPermissionDenied() // 用户点击了取消，执行失败回调
            }
        )
    }
}

/**
 * 使用 accompanist-permissions 库处理标准的运行时权限。
 */
@OptIn(ExperimentalPermissionsApi::class)
@Composable
private fun StandardPermissionHandler(
    permissions: List<String>,
    onPermissionGranted: () -> Unit,
    onPermissionDenied: () -> Unit,
) {
    val context = LocalContext.current
    val permissionsState = rememberMultiplePermissionsState(permissions)
    var showRationaleDialog by remember { mutableStateOf(false) }
    var showSettingsDialog by remember { mutableStateOf(false) }

    // `LaunchedEffect` 用于在权限状态变化时触发请求，这是 accompanist-permissions 的标准用法
    LaunchedEffect(permissionsState.allPermissionsGranted) {
        if (!permissionsState.allPermissionsGranted && !permissionsState.shouldShowRationale) {
            permissionsState.launchMultiplePermissionRequest()
        }
    }

    when {
        // 情况一：所有权限都已授予
        permissionsState.allPermissionsGranted -> {
            onPermissionGranted()
        }
        // 情况二：权限被拒绝，且系统建议我们向用户解释原因（用户至少拒绝过一次）
        permissionsState.shouldShowRationale -> {
            showRationaleDialog = true
        }
        // 情况三：权限被永久拒绝（用户勾选了“不再询问”）
        !permissionsState.allPermissionsGranted && !permissionsState.shouldShowRationale -> {
            showSettingsDialog = true
        }
    }

    // 显示解释原因的对话框（用户拒绝后）
    if (showRationaleDialog) {
        PermissionDialog(
            title = "需要权限",
            message = "此功能需要您授予相关权限才能继续使用。",
            confirmText = "再次请求",
            onConfirm = {
                permissionsState.launchMultiplePermissionRequest()
                showRationaleDialog = false
            },
            onDismiss = {
                showRationaleDialog = false
                onPermissionDenied()
            }
        )
    }

    // 显示引导用户去设置的对话框（用户永久拒绝后）
    if (showSettingsDialog) {
        PermissionDialog(
            title = "权限被拒绝",
            message = "部分必要权限已被永久拒绝。请前往系统设置页面手动开启。",
            confirmText = "前往设置",
            onConfirm = {
                val intent = Intent(Settings.ACTION_APPLICATION_DETAILS_SETTINGS).apply {
                    data = Uri.parse("package:${context.packageName}")
                    flags = Intent.FLAG_ACTIVITY_NEW_TASK
                }
                context.startActivity(intent)
                showSettingsDialog = false
            },
            onDismiss = {
                showSettingsDialog = false
                onPermissionDenied()
            }
        )
    }
}


/**
 * 通用的权限提示对话框
 */
@Composable
fun PermissionDialog(
    title: String,
    message: String,
    confirmText: String,
    onConfirm: () -> Unit,
    onDismiss: () -> Unit,
) {
    AlertDialog(
        onDismissRequest = onDismiss,
        title = { Text(title) },
        text = { Text(message) },
        confirmButton = {
            TextButton(onClick = onConfirm) {
                Text(confirmText)
            }
        },
        dismissButton = {
            TextButton(onClick = onDismiss) {
                Text("取消")
            }
        }
    )
}

@Composable
fun ConfirmDialog(
    title: String,
    message: String,
    onConfirm: () -> Unit,
    onDismiss: () -> Unit,
    confirmText: String = "确认",
    dismissText: String = "取消"
) {
    Dialog(onDismissRequest = onDismiss) {
        Surface(
            shape = MaterialTheme.shapes.medium,
            tonalElevation = 6.dp,
            color = MaterialTheme.colorScheme.surface,
            modifier = Modifier
                .fillMaxWidth()
                .padding(16.dp)
        ) {
            Column(
                modifier = Modifier.padding(24.dp),
                verticalArrangement = Arrangement.spacedBy(16.dp)
            ) {
                Text(
                    text = title,
                    style = MaterialTheme.typography.titleLarge,
                    color = MaterialTheme.colorScheme.onSurface
                )

                Text(
                    text = message,
                    style = MaterialTheme.typography.bodyMedium,
                    color = MaterialTheme.colorScheme.onSurfaceVariant,
                    textAlign = TextAlign.Start
                )

                Row(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(top = 8.dp),
                    horizontalArrangement = Arrangement.End
                ) {
                    TextButton(onClick = onDismiss) {
                        Text(dismissText)
                    }
                    Spacer(modifier = Modifier.width(8.dp))
                    TextButton(onClick = onConfirm) {
                        Text(confirmText)
                    }
                }
            }
        }
    }
}
