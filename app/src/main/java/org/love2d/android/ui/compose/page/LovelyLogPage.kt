package org.love2d.android.ui.compose.page

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.gestures.rememberTransformableState
import androidx.compose.foundation.gestures.transformable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.text.selection.SelectionContainer
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ArrowBack
import androidx.compose.material.icons.automirrored.filled.Note
import androidx.compose.material.icons.filled.Share
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.activity.Screen
import org.love2d.android.ui.compose.EmptyLottie
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.ShareUtil
import java.io.File

/**
 * 日志列表页面 - 美化版本
 */
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun EnhancedLovelyLogPage(navController: NavController, viewModel: GameManagerViewModel) {
    val context = LocalContext.current
    val gameInfo by viewModel.currentGame.collectAsState()
    val files = remember(gameInfo) {
        gameInfo?.modPath?.let { FileSelectorUtil.getLovelyLogList(context, it) }
    }

    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text("日志列表") },
                navigationIcon = {
                    IconButton(onClick = { navController.popBackStack() }) {
                        Icon(Icons.AutoMirrored.Filled.ArrowBack, contentDescription = "返回")
                    }
                }
            )
        }
    ) { innerPadding ->
        if (files.isNullOrEmpty()) {
            Box(modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding), contentAlignment = Alignment.Center) {
                EmptyLottie(emptyText = "暂无日志文件", isShowAdd = false)
            }
        } else {
            LazyColumn(
                modifier = Modifier
                    .fillMaxSize()
                    .padding(innerPadding),
                contentPadding = PaddingValues(16.dp),
                verticalArrangement = Arrangement.spacedBy(12.dp)
            ) {
                items(files, key = { it.absolutePath }) { file ->
                    LogFileRow(
                        file = file,
                        onViewClick = {
                            viewModel.currentLovelyFile.value = it
                            navController.navigate(Screen.LOG_DETAIL.name)
                        }
                    )
                }
            }
        }
    }
}

/**
 * 统一的日志文件信息行，代替了旧的 Card
 */
@Composable
fun LogFileRow(file: File, onViewClick: (File) -> Unit) {
    val context = LocalContext.current
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(16.dp))
            .background(MaterialTheme.colorScheme.surfaceContainer)
            .clickable { onViewClick(file) }
            .padding(horizontal = 16.dp, vertical = 12.dp),
        verticalAlignment = Alignment.CenterVertically
    ) {
        Icon(
            imageVector = Icons.AutoMirrored.Filled.Note,
            contentDescription = "日志文件",
            tint = MaterialTheme.colorScheme.primary,
            modifier = Modifier.padding(end = 16.dp)
        )
        Text(
            text = file.name.removeSuffix(".log"),
            modifier = Modifier.weight(1f),
            style = MaterialTheme.typography.bodyLarge,
            maxLines = 2,
            overflow = TextOverflow.Ellipsis,
            fontWeight = FontWeight.Medium
        )
        // 分享按钮
        IconButton(
            onClick = { ShareUtil.shareFile(context, file.absolutePath) },
        ) {
            Icon(
                imageVector = Icons.Default.Share,
                contentDescription = "分享",
                tint = MaterialTheme.colorScheme.secondary
            )
        }
    }
}


/**
 * 日志详情页面 - 使用了新的代码编辑器风格的缩放控件
 */
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun EnhancedLogDetailPage(navController: NavController, viewModel: GameManagerViewModel) {
    val logFile by viewModel.currentLovelyFile.collectAsState()
    val context = LocalContext.current

    Scaffold(
        topBar = {
            TopAppBar(
                title = {
                    Text(
                        text = logFile?.name ?: "日志详情",
                        maxLines = 1,
                        overflow = TextOverflow.Ellipsis
                    )
                },
                navigationIcon = {
                    IconButton(onClick = { navController.popBackStack() }) {
                        Icon(Icons.AutoMirrored.Filled.ArrowBack, contentDescription = "返回")
                    }
                },
                actions = {
                    logFile?.let { file ->
                        IconButton(onClick = { ShareUtil.shareFile(context, file.absolutePath) }) {
                            Icon(Icons.Default.Share, contentDescription = "分享日志")
                        }
                    }
                }
            )
        }
    ) { innerPadding ->
        Box(
            modifier = Modifier
                .fillMaxSize()
                .padding(innerPadding)
        ) {
            logFile?.let {
                // 使用全新的、代码编辑器风格的缩放查看器
                CodeStyleZoomableViewer(logFile = it)
            } ?: Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
                Text("未找到日志文件")
            }
        }
    }
}


/**
 * 全新的、代码编辑器风格的文本缩放查看器
 */
@Composable
fun CodeStyleZoomableViewer(logFile: File) {
    // 1. 状态现在是字体大小(fontSize)，而不是缩放比例(scale)
    var fontSize by remember { mutableStateOf(8.sp) }

    // 2. remember 内部的逻辑保持不变，但现在读取的是文件内容
    val text = remember(logFile) { readLogFile(logFile) }

    val transformableState = rememberTransformableState { zoomChange, _, _ ->
        fontSize = (fontSize.value * zoomChange)
            .coerceIn(8f, 40f) // 限制放大倍数
            .sp
    }

    // 将 transformable 手势识别应用到整个 Box 区域
    Box(
        modifier = Modifier
            .fillMaxSize()
            .transformable(state = transformableState)
    ) {
        // 为了获得良好的滚动体验，内层使用一个可滚动的 Box
        Box(
            modifier = Modifier
                .fillMaxSize()
                .verticalScroll(rememberScrollState())
        ) {
            SelectionContainer {
                Text(
                    text = text,
                    modifier = Modifier.padding(16.dp),
                    fontSize = fontSize,
                    lineHeight = fontSize * 1.5
                )
            }
        }
    }
}

/**
 * 读取日志文件的辅助函数 (保持不变)
 */
fun readLogFile(file: File): String {
    return try {
        if (file.exists()) file.readText() else "文件不存在或无法读取"
    } catch (e: Exception) {
        "读取文件时发生错误: ${e.message}"
    }
}