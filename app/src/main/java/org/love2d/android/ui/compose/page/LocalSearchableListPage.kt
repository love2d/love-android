package org.love2d.android.ui.compose.page

import android.util.Log
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.ExperimentalLayoutApi
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.isImeVisible
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.statusBars
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.layout.windowInsetsPadding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material.icons.filled.Check
import androidx.compose.material.icons.filled.Close
import androidx.compose.material.icons.filled.Search
import androidx.compose.material.icons.filled.Sort
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TextFieldDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalFocusManager
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.zIndex
import androidx.navigation.NavController
import org.love2d.android.ui.activity.GameManagerViewModel
import java.io.File

/**
 * ClassName SearchableListPage
 * Description 带有可折叠搜索栏的页面框架
 * Create by hjr
 * Date 2025/7/2 16:17
 */

@OptIn(ExperimentalLayoutApi::class)
@Composable
fun DownloadInfoModPage(
    navController: NavController,
    viewModel: GameManagerViewModel,
) {
    val context = LocalContext.current

    var currentQuery by remember { mutableStateOf("") }
    var currentSort by remember { mutableStateOf("stars") }

    val focusManager = LocalFocusManager.current
    val isKeyboardOpen = WindowInsets.isImeVisible

    LaunchedEffect(isKeyboardOpen) {
        if (!isKeyboardOpen) {
            focusManager.clearFocus()
        }

        val file = File(context.filesDir, "download_mods")
        file.listFiles()?.forEach {
            Log.e("HJR", "download_mods fileName = ${it.name}")
        }
    }

    Surface(
        modifier = Modifier.fillMaxSize(),
    ) {
        Box(modifier = Modifier.fillMaxSize()) {
            Column(
                Modifier
                    .fillMaxSize()
            ) {
                DownloadInfoAdaptivePinnedHeader(
                    navController,
                    viewModel,
                    currentSort = currentSort,
                    onSortClick = { sortKey ->
                        currentSort = sortKey
                        if (currentQuery.isNotBlank()) {
                            viewModel.searchMods(currentQuery, true, currentSort)
                        } else {
                            viewModel.getModList(true, currentSort)
                        }
                    },
                    onSearchChanged = {
                        currentQuery = it
                    },
                )
                DownloadModShopPage(viewModel = viewModel, query = currentQuery,sort = currentSort)
            }
        }
    }
}

/**
 * 【核心修正】使用 Surface 构建的、高度自适应的固定头部。
 */
@Composable
fun DownloadInfoAdaptivePinnedHeader(
    navController: NavController,
    viewModel: GameManagerViewModel,
    onSortClick: (String) -> Unit,
    currentSort : String = "stars",
    onSearchChanged: (String) -> Unit,
) {
    // 1. 使用 Surface 作为根容器，它没有高度限制。
    //    设置 tonalElevation 可以让它看起来像一个悬浮的工具栏。
    var isShowSort by remember { mutableStateOf(false) }
    Surface(
        modifier = Modifier
            .fillMaxWidth()
            .zIndex(1f),
        shadowElevation = 3.dp, // 增加一点阴影使其与内容区分
        tonalElevation = 3.dp
    ) {
        // 2. 内部布局和之前完全一样，使用 Column 垂直排列
        Column(
            modifier = Modifier
                // 增加一些内边距，让布局更好看
                .padding(horizontal = 16.dp, vertical = 12.dp)
                .fillMaxWidth()
                .windowInsetsPadding(WindowInsets.statusBars)
        ) {
            Box(
                modifier = Modifier
                    .fillMaxWidth()
            ) {
                // 左上角的返回按钮
                Icon(
                    Icons.Default.ArrowBack,
                    contentDescription = Icons.Default.ArrowBack.name,
                    modifier = Modifier
                        .align(Alignment.CenterStart)
                        .clickable { navController.popBackStack() }
                )

                // 居中的标题
                Text(
                    text = "下载列表",
                    style = MaterialTheme.typography.titleLarge,
                    fontWeight = FontWeight.Bold,
                    modifier = Modifier.align(Alignment.Center)
                )
            }
            Spacer(modifier = Modifier.height(12.dp))
            // 第二行：控件行
            Row(
                modifier = Modifier.fillMaxWidth(),
                verticalAlignment = Alignment.CenterVertically,
                horizontalArrangement = Arrangement.spacedBy(8.dp)
            ) {
                var searchQuery by remember { mutableStateOf("") }
                // 搜索框
                TextField(
                    value = searchQuery,
                    onValueChange = {
                        searchQuery = it
                        onSearchChanged(it)
                    },
                    modifier = Modifier
                        .weight(1f),
                    placeholder = { Text("搜索...") },
                    leadingIcon = { Icon(Icons.Default.Search, contentDescription = "搜索") },
                    trailingIcon = {
                        if (searchQuery.isNotEmpty()) {
                            Icon(
                                imageVector = Icons.Filled.Close,
                                contentDescription = Icons.Filled.Close.name,
                                modifier = Modifier
                                    .clickable {
                                        searchQuery = ""
                                        onSearchChanged(searchQuery)
                                        viewModel.getModList(true)
                                    }
                            )
                        }
                    },
                    shape = RoundedCornerShape(16.dp),
                    singleLine = true,
                    colors = TextFieldDefaults.colors(
                        focusedIndicatorColor = Color.Transparent,
                        unfocusedIndicatorColor = Color.Transparent,
                        disabledIndicatorColor = Color.Transparent,
                    )
                )
                // 排序按钮 + 菜单绑定
                Box {
                    IconButton(onClick = { isShowSort = true }) {
                        Icon(Icons.Default.Sort, contentDescription = "排序")
                    }

                    DropdownMenu(
                        expanded = isShowSort,
                        onDismissRequest = { isShowSort = false }
                    ) {
                        mapOf(
                            "stars" to "按星星数排序",
                            "downloads" to "按下载量排序"
                        ).forEach {
                            DropdownMenuItem(
                                text = {
                                    Row(
                                        verticalAlignment = Alignment.CenterVertically
                                    ) {
                                        Text(
                                            text = it.value,
                                            color = if (it.key == currentSort) MaterialTheme.colorScheme.primary
                                            else MaterialTheme.colorScheme.onSurface
                                        )
                                        if (it.key == currentSort) {
                                            Spacer(modifier = Modifier.width(8.dp))
                                            Icon(
                                                imageVector = Icons.Default.Check,
                                                contentDescription = "已选中",
                                                tint = MaterialTheme.colorScheme.primary,
                                                modifier = Modifier.size(16.dp)
                                            )
                                        }
                                    }
                                },
                                onClick = {
                                    isShowSort = false
                                    onSortClick(it.key)
                                }
                            )
                        }
                    }
                }
            }
        }
    }
}