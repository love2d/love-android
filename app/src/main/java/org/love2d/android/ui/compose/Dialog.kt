package org.love2d.android.ui.compose

import android.util.Log
import android.widget.Toast
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Close
import androidx.compose.material3.Button
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.window.Dialog
import androidx.compose.ui.window.DialogProperties
import org.love2d.android.AppConfig.userNotice
import org.love2d.android.room.game.GameInfo
import org.love2d.android.ui.compose.page.CameraQrScanner
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.GameStartUtil

/**
 * ClassName Dialog
 * Description
 * Create by hjr
 * Date 2025/6/20 12:23
 */


@Composable
fun UserNoticeDialog(show: Boolean, onDismiss: () -> Unit) {
    if (show) {
        Dialog(
            onDismissRequest = onDismiss,
            properties = DialogProperties(
                dismissOnClickOutside = false, // ❌点击外部不关闭
                dismissOnBackPress = false     // ❌按返回键不关闭
            )
        ) {
            Surface(
                shape = RoundedCornerShape(12.dp),
                tonalElevation = 8.dp,
                modifier = Modifier
                    .padding(16.dp)
                    .fillMaxWidth()
            ) {
                Column(
                    modifier = Modifier
                        .padding(20.dp)
                        .verticalScroll(rememberScrollState())
                ) {
                    Text(
                        text = "用户须知",
                        style = MaterialTheme.typography.titleLarge,
                        modifier = Modifier.align(Alignment.CenterHorizontally)
                    )
                    Spacer(modifier = Modifier.height(16.dp))
                    Text(
                        text = userNotice,
                        style = MaterialTheme.typography.bodyMedium,
                        lineHeight = 22.sp
                    )
                    Spacer(modifier = Modifier.height(24.dp))
                    Button(
                        onClick = onDismiss,
                        modifier = Modifier.align(Alignment.CenterHorizontally)
                    ) {
                        Text("我已知晓")
                    }
                }
            }
        }
    }
}

@Composable
fun GameNameInputDialog(
    gameName: String,
    onDismiss: () -> Unit,
    onConfirm: (String) -> Unit,
    onNameChanged: (String) -> Unit,
    isShowDismissBtn: Boolean = false,
) {
    val context = LocalContext.current
    val pattern = remember { Regex("^[a-zA-Z0-9]+$") }

    val trimGameName = gameName.trim()
    Dialog(
        onDismissRequest = { onDismiss() },
        properties = DialogProperties(
            dismissOnClickOutside = isShowDismissBtn, // ❌点击外部不关闭
            dismissOnBackPress = isShowDismissBtn     // ❌按返回键不关闭
        )
    ) {
        Surface(
            shape = RoundedCornerShape(12.dp),
            tonalElevation = 8.dp,
            modifier = Modifier
                .padding(16.dp)
                .fillMaxWidth()
        ) {
            Column(
                modifier = Modifier
                    .padding(20.dp)
            ) {
                Text(
                    text = "输入游戏名称",
                    style = MaterialTheme.typography.titleLarge,
                    modifier = Modifier.align(Alignment.CenterHorizontally)
                )
                Spacer(modifier = Modifier.height(16.dp))
                TextField(
                    // 1. 直接使用 gameName，不要在这里 trim
                    value = gameName,
                    onValueChange = { newValue ->
                        // 2. 直接判断新输入的值
                        // 允许输入为空，或者输入符合正则表达式
                        if (newValue.isEmpty() || pattern.matches(newValue)) {
                            onNameChanged(newValue)
                        } else {
                            Toast.makeText(context, "仅允许输入英文、数字和空格。", Toast.LENGTH_SHORT)
                                .show()
                        }
                    },
                    placeholder = { Text("输入游戏名称") }
                )
                Spacer(modifier = Modifier.height(24.dp))
                Row(
                    modifier = Modifier.fillMaxWidth()
                ) {
                    Button(
                        onClick = {
                            if (trimGameName.isEmpty()) {
                                Toast.makeText(
                                    context,
                                    "请输入游戏名称",
                                    Toast.LENGTH_SHORT
                                ).show()
                            } else {
                                if (!FileSelectorUtil.checkGameFileExists(trimGameName)) {
                                    onConfirm(trimGameName)
                                } else {
                                    Toast.makeText(
                                        context,
                                        "游戏名称已存在",
                                        Toast.LENGTH_SHORT
                                    ).show()
                                }
                            }
                        },
                        modifier = Modifier
                            .align(Alignment.CenterVertically)
                            .fillMaxWidth()
                            .weight(1f)
                    ) {
                        Text("确认")
                    }
                    if (isShowDismissBtn) {
                        Spacer(modifier = Modifier.width(30.dp))
                        Button(
                            onClick = onDismiss,
                            modifier = Modifier
                                .align(Alignment.CenterVertically)
                                .fillMaxWidth()
                                .weight(1f)
                        ) {
                            Text("取消")
                        }
                    }
                }
            }
        }
    }
}

@Composable
fun GameRunningTipDialog(
    readyGame: GameInfo,
    onDismiss: () -> Unit,
) {
    val context = LocalContext.current

    val running = GameStartUtil.currentRunningGame.collectAsState()

    Dialog(onDismissRequest = onDismiss) {
        Surface(
            shape = RoundedCornerShape(16.dp),
            tonalElevation = 8.dp,
            modifier = Modifier
                .padding(24.dp)
                .fillMaxWidth()
        ) {
            Box(modifier = Modifier.padding(14.dp)) {
                // 右上角关闭按钮
                Box(modifier = Modifier.fillMaxWidth()) {
                    IconButton(
                        onClick = onDismiss,
                        modifier = Modifier.align(Alignment.TopEnd)
                    ) {
                        Icon(
                            imageVector = Icons.Default.Close,
                            contentDescription = "关闭"
                        )
                    }
                }

                Column(
                    modifier = Modifier.fillMaxWidth(),
                    horizontalAlignment = Alignment.CenterHorizontally
                ) {
                    Spacer(modifier = Modifier.height(8.dp))
                    Text(
                        text = "提示",
                        style = MaterialTheme.typography.titleLarge,
                        color = MaterialTheme.colorScheme.onSurface
                    )
                    Spacer(modifier = Modifier.height(12.dp))
                    Text(
                        text = "当前 ${running.value?.second?.name} 已在运行中，是否继续？结束并启动可能会导致游戏数据丢失。",
                        style = MaterialTheme.typography.bodyLarge,
                        fontSize = 12.sp
                    )
                    Spacer(modifier = Modifier.height(24.dp))

                    Row(
                        modifier = Modifier.fillMaxWidth(),
                        horizontalArrangement = Arrangement.spacedBy(5.dp)
                    ) {
                        Button(
                            onClick = {
                                GameStartUtil.shutdownAndRestartGame(context, readyGame)
                                onDismiss()
                            },
                            modifier = Modifier.weight(1f)
                        ) {
                            Text("结束并启动")
                        }

                        Button(
                            onClick = {
                                GameStartUtil.bringGameToFront(context)
                                onDismiss()
                            },
                            modifier = Modifier.weight(1f),
                        ) {
                            Text("回到游戏")
                        }
                    }
                }
            }
        }
    }
}

@Composable
fun ScanQrCodeDialog(
    onDismiss: () -> Unit,
    status : String,
    scanned : Boolean,
    scannedRunning : Boolean,
    onSync : () -> Unit,
    onDisconnect : () -> Unit,
    onScanned : (String) -> Unit
) {
    Dialog(onDismissRequest = onDismiss) {
        Surface(
            shape = RoundedCornerShape(16.dp),
            tonalElevation = 8.dp,
            modifier = Modifier
                .padding(24.dp)
                .fillMaxWidth()
        ) {
            Box(modifier = Modifier.padding(14.dp)) {
                Column(
                    modifier = Modifier.fillMaxWidth(),
                    horizontalAlignment = Alignment.CenterHorizontally
                ) {
                    Spacer(modifier = Modifier.height(8.dp))
                    Text(
                        text = "无线连接",
                        style = MaterialTheme.typography.titleLarge,
                        color = MaterialTheme.colorScheme.onSurface
                    )
                    Spacer(modifier = Modifier.height(12.dp))
                    Text(
                        text = "连接状态: $status",
                        style = MaterialTheme.typography.bodyLarge,
                        fontSize = 12.sp
                    )
                    Spacer(modifier = Modifier.height(12.dp))
                    Box(modifier = Modifier.fillMaxWidth(), contentAlignment = Alignment.Center) {
                        Log.e("HJR","scanned = $scanned | !scanned = ${!scanned}")
                        CameraQrScanner(
                            modifier = Modifier
                                .size(250.dp)
                                .clip(RoundedCornerShape(16.dp)),
                            shouldScan = !scanned,
                            screenRunning = scannedRunning,
                        ) { scanned ->
                           onScanned(scanned)
                        }
                    }
                    Spacer(modifier = Modifier.height(24.dp))
                    if (scanned) {
                        Button(onClick = onSync) {
                            Text(text = "同步")
                        }
                        Button(onClick = onDisconnect) {
                            Text(text = "断开连接")
                        }
                    }
                    Button(onClick = onDismiss) {
                        Text(text = "关闭")
                    }
                }
            }
        }
    }
}

