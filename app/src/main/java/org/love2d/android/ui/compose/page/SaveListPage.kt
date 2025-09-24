package org.love2d.android.ui.compose.page

import android.content.Context
import android.util.Log
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.gestures.Orientation
import androidx.compose.foundation.interaction.MutableInteractionSource
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.IntrinsicSize
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.offset
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.safeDrawing
import androidx.compose.foundation.layout.windowInsetsPadding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.ExperimentalMaterialApi
import androidx.compose.material.FractionalThreshold
import androidx.compose.material.SwipeableState
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.FolderOpen
import androidx.compose.material.icons.filled.Share
import androidx.compose.material.rememberSwipeableState
import androidx.compose.material.swipeable
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.ExtendedFloatingActionButton
import androidx.compose.material3.FabPosition
import androidx.compose.material3.FilledIconButton
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.IconButtonDefaults
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.RadioButton
import androidx.compose.material3.RadioButtonDefaults
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.runtime.snapshotFlow
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.IntOffset
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.distinctUntilChanged
import kotlinx.coroutines.launch
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.compose.EmptyLottie
import org.love2d.android.ui.compose.ScanQrCodeDialog
import org.love2d.android.ui.compose.TopTitleBar
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.ShareUtil
import org.love2d.android.util.WebSocketManager
import java.io.File
import kotlin.math.roundToInt

/**
 * ClassName SaveListPage
 * Description
 * Create by hjr
 * Date 2025/7/7 09:39
 */
@OptIn(ExperimentalMaterial3Api::class, ExperimentalMaterialApi::class)
@Composable
fun SaveListPage(navController: NavController, viewModel: GameManagerViewModel) {
    val context = LocalContext.current

    val connected = WebSocketManager.isConnected()
    val currentStatus = WebSocketManager.getCurrentStatus()
    var wsUrl by remember { mutableStateOf("") }
    var status by remember { mutableStateOf(currentStatus) }
    var scanned by remember { mutableStateOf(connected) }
    var scannedRunning by remember { mutableStateOf(false) }
    var isShowQr by remember { mutableStateOf(false) }

    val gameInfoState = viewModel.currentGame.collectAsState()

    val files = getAllSaveFiles(context)
    val strings = gameInfoState.value!!.savePath.split("/")
    val currentName = remember {
        mutableStateOf(strings.last())
    }
    val swipeStates = remember { mutableStateListOf<SwipeableState<Int>>() }
    val coroutineScope = rememberCoroutineScope()

    Scaffold(modifier = Modifier
        .fillMaxSize()
        .windowInsetsPadding(WindowInsets.safeDrawing), topBar = {
        TopTitleBar(navController = navController, title = "存档管理")
    }, floatingActionButton = {
        ExtendedFloatingActionButton(onClick = {
            isShowQr = true
        },
            containerColor = MaterialTheme.colorScheme.primary,
            contentColor = MaterialTheme.colorScheme.onPrimary,
            icon = {
                Icon(
                    Icons.Default.Add, contentDescription = null
                )
            },
            text = { Text("导入") })
    }, floatingActionButtonPosition = FabPosition.End
    ) { innerPadding ->
        if (files.isNullOrEmpty()) {
            Box(
                modifier = Modifier
                    .fillMaxSize()
                    .padding(innerPadding), contentAlignment = Alignment.Center
            ) {
                EmptyLottie(emptyText = "暂无存档文件", isShowAdd = false)
            }
        } else {
            Box(modifier = Modifier
                .fillMaxSize()
                .clickable(indication = null, interactionSource = remember { MutableInteractionSource() }) {
                    swipeStates.forEach {
                        if (it.offset.value != 0f) {
                            coroutineScope.launch { it.animateTo(0) }
                        }
                    }
                }) {
                LazyColumn(
                    modifier = Modifier
                        .fillMaxSize()
                        .padding(innerPadding),
                    contentPadding = PaddingValues(16.dp),
                    verticalArrangement = Arrangement.spacedBy(12.dp)
                ) {
                    items(files.size) {
                        SwipeableSaveFileRow(file = files[it], currentName = currentName.value, onViewClick = {
                            //打印
                            it.listFiles()?.forEach {
                                Log.e("HJR-Save","${it.name}")
                            }
                        }, onSelect = { selectFile ->
                            currentName.value = selectFile.nameWithoutExtension
                            gameInfoState.value!!.savePath = selectFile.absolutePath
                            viewModel.update(gameInfoState.value!!)
                        }, onDelete = {

                        }, swipeStates = swipeStates, coroutineScope = coroutineScope
                        )
                    }
                }

                if (isShowQr) {
                    ScanQrCodeDialog(
                        onDismiss = { isShowQr = false },
                        status = status,
                        scanned = scanned,
                        scannedRunning = scannedRunning,
                        onSync = {
                            WebSocketManager.sendSync()
                        },
                        onDisconnect = {
                            WebSocketManager.disconnect {
                                scannedRunning = false
                                scanned = false
                            }
                        }
                    ) { scannedValue ->
                        if (scannedRunning) return@ScanQrCodeDialog // 🛑 阻止多次触发
                        scannedRunning = true
                        if (!WebSocketManager.isConnected()) {
                            WebSocketManager.connect(scannedValue) { update ->
                                status = update
                                if (update == "已连接") {
                                    scanned = true
                                }
                                scannedRunning = false
                            }
                        } else {
                            scannedRunning = false
                        }
                    }
                }
            }
        }
    }
}

@OptIn(ExperimentalMaterialApi::class)
@Composable
fun SwipeableSaveFileRow(
    file: File,
    currentName: String,
    onViewClick: (File) -> Unit,
    onSelect: (File) -> Unit,
    onDelete: (File) -> Unit,
    swipeStates: MutableList<SwipeableState<Int>>,
    coroutineScope: CoroutineScope,
) {
    val swipeState = rememberSwipeableState(0)
    val widthInPx = with(LocalDensity.current) { 80.dp.toPx() }
    val anchors = mapOf(0f to 0, -widthInPx to 1)

    // [保留] 使用 DisposableEffect 保证状态管理的正确性
    DisposableEffect(swipeState) {
        swipeStates.add(swipeState)
        onDispose {
            swipeStates.remove(swipeState)
        }
    }

    // [最终修复] 在触发关闭动画前，检查目标项是否已在执行动画
    LaunchedEffect(swipeState) {
        snapshotFlow { swipeState.offset.value }
            .distinctUntilChanged()
            .collect { offset ->
                if (offset != 0f) {
                    swipeStates
                        // [核心修改] 增加 !it.isAnimationRunning 判断
                        // 确保只对那些处于打开状态、且当前没有在播放动画的项，下达一次关闭指令
                        .filter { it != swipeState && it.currentValue != 0 && !it.isAnimationRunning }
                        .forEach { otherState ->
                            coroutineScope.launch {
                                otherState.animateTo(0)
                            }
                        }
                }
            }
    }

    Box(
        modifier = Modifier
            .fillMaxWidth()
            .height(IntrinsicSize.Min)
            .swipeable(
                state = swipeState,
                anchors = anchors,
                thresholds = { _, _ -> FractionalThreshold(0.2f) },
                orientation = Orientation.Horizontal
            )
    ) {
        // 背后：删除按钮
        Box(
            modifier = Modifier
                .fillMaxSize()
                .padding(end = 14.dp), contentAlignment = Alignment.CenterEnd
        ) {
            FilledIconButton(
                onClick = {
                    onDelete(file)
                    coroutineScope.launch { swipeState.snapTo(0) }
                }, colors = IconButtonDefaults.filledIconButtonColors(
                    containerColor = MaterialTheme.colorScheme.error, contentColor = MaterialTheme.colorScheme.onError
                )
            ) {
                Icon(Icons.Default.Delete, contentDescription = "删除")
            }
        }

        // 前面：内容项，滑动
        Box(modifier = Modifier.offset { IntOffset(swipeState.offset.value.roundToInt(), 0) }) {
            SaveFileRow(
                file = file, currentName = currentName, onViewClick = onViewClick, onSelect = onSelect
            )
        }
    }
}

@Composable
fun SaveFileRow(file: File, currentName: String, onViewClick: (File) -> Unit, onSelect: (File) -> Unit) {
    val context = LocalContext.current
    Row(modifier = Modifier
        .fillMaxWidth()
        .clip(RoundedCornerShape(16.dp))
        .background(MaterialTheme.colorScheme.surfaceContainer)
        .clickable { onViewClick(file) }
        .padding(horizontal = 16.dp, vertical = 12.dp),
        verticalAlignment = Alignment.CenterVertically) {
        Icon(
            imageVector = Icons.Filled.FolderOpen,
            contentDescription = "存档文件",
            tint = MaterialTheme.colorScheme.primary,
            modifier = Modifier.padding(end = 16.dp)
        )
        Text(
            text = file.name,
            modifier = Modifier.weight(1f),
            style = MaterialTheme.typography.bodyLarge,
            maxLines = 2,
            overflow = TextOverflow.Ellipsis,
            fontWeight = FontWeight.Medium
        )
        RadioButton(
            selected = currentName == file.nameWithoutExtension, onClick = {
                onSelect(file)
            }, colors = RadioButtonDefaults.colors(
                selectedColor = MaterialTheme.colorScheme.primary,    // 选中颜色
                unselectedColor = MaterialTheme.colorScheme.onSurfaceVariant // 未选中颜色
            )
        )
        // 分享按钮
        IconButton(
            onClick = {
                val saveZipFile = File(context.cacheDir, "${file.nameWithoutExtension}.zip")
                FileSelectorUtil.zipDirectory(file, saveZipFile)
                ShareUtil.shareFile(context, saveZipFile.absolutePath)
            },
        ) {
            Icon(
                imageVector = Icons.Default.Share, contentDescription = "分享", tint = MaterialTheme.colorScheme.secondary
            )
        }
    }
}

fun getAllSaveFiles(context: Context): List<File>? {
    val file = File(context.getExternalFilesDir(null), "save/love")
    return file.listFiles()?.toList()
}

fun getSaveFile(context: Context, gameName: String?): File {
    return File(context.getExternalFilesDir(null), "save/love/$gameName-LOVE")
}