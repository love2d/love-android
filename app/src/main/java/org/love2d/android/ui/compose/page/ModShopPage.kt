package org.love2d.android.ui.compose.page

import android.content.Intent
import android.util.Log
import androidx.compose.foundation.background
import androidx.compose.foundation.basicMarquee
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.navigationBars
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.layout.windowInsetsPadding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Check
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.Download
import androidx.compose.material.icons.filled.Link
import androidx.compose.material.icons.filled.Star
// NEW: Import the 'Update' icon for the new button.
import androidx.compose.material.icons.filled.Update
import androidx.compose.material.icons.outlined.History
import androidx.compose.material.icons.outlined.Info
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.FloatingActionButtonDefaults
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.core.net.toUri
import coil.compose.AsyncImage
import org.love2d.android.net.UiState
import org.love2d.android.room.download.DownloadInfo
import org.love2d.android.ui.activity.DownloadState
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.activity.ModListState
import org.love2d.android.util.startNetUri

/**
 * ClassName ModShopPage
 * Description
 * Create by hjr
 * Date 2025/7/1 16:10
 */

@Composable
fun ModShopPage(viewModel: GameManagerViewModel, query: String, sort: String) {

    val downloadStates by viewModel.downloadStates.collectAsState()
    val context = LocalContext.current

    // 当 query 发生变化时，这个代码块会被触发
    LaunchedEffect(query) {
        if (query.isBlank()) {
            // 如果 query 为空，说明是浏览模式，可以按需加载主列表
            // 为了避免重复加载，可以加一个判断
            if (viewModel.modUiState.value !is UiState.Success) {
                viewModel.getModList()
            }
        } else {
            // 如果 query 不为空，则执行新的搜索
            viewModel.searchMods(query, isNewSearch = true)
        }
    }

    // NEW: In your ViewModel, you must implement the logic to compare the version of
    // the fetched mods against your locally stored mods. Based on that comparison,
    // you will populate the `downloadStates` map with `DownloadState.Updatable` or
    // `DownloadState.Installed` for the UI to consume.
    if (query.isBlank()) {
        val uiState by viewModel.modUiState.collectAsState()
        // 1. 从 viewModel 收集下载状态
        ModListContent(
            uiState = uiState,
            // 2. 将状态传递给 ModListContent
            downloadStates = downloadStates,
            onLoadMore = { viewModel.getModList() },
            onRetry = { viewModel.getModList(isRefresh = true) },
            onInstallClick = { mod ->
                // NEW: This single function call now handles both new downloads and updates.
                // Your ViewModel's `downloadMod` function should check if the mod
                // already exists. If it's an update, it should delete the old file
                // before proceeding with the download.
                viewModel.downloadMod(mod, context = context)
            },
            sort = sort
        )
    } else {
        val searchState by viewModel.searchUiState.collectAsState()
        ModListContent(
            uiState = searchState,
            downloadStates = downloadStates,
            onLoadMore = { viewModel.searchMods(query, isNewSearch = false) },
            onRetry = { viewModel.searchMods(query, isNewSearch = true) },
            onInstallClick = { mod ->
                viewModel.downloadMod(mod, context = context)
            },
            sort = sort
        )
    }
}
@Composable
fun EnhancedModShopCard(
    mod: DownloadInfo,
    sort: String,
    downloadState: DownloadState, // 接收具体的下载状态
    onInstallClick: (DownloadInfo) -> Unit,
    modifier: Modifier = Modifier,
) {
    // 在这里加一行日志，用于调试
    Log.e("HJR", "Download Mod: ${mod.name}, State: $downloadState")

    Column(
        modifier = modifier
            .fillMaxWidth()
            .background(MaterialTheme.colorScheme.surfaceContainer, RoundedCornerShape(24.dp))
            .padding(16.dp)
    ) {
        // 作者信息
        AuthorInfo(
            avatarUrl = mod.author_avatar_url,
            author = mod.author,
            repoUrl = mod.github_repo_url
        )

        Spacer(modifier = Modifier.height(16.dp))

        // Mod 详情
        Text(
            text = mod.name,
            style = MaterialTheme.typography.headlineMedium,
            fontWeight = FontWeight.Bold,
            color = MaterialTheme.colorScheme.primary
        )

        Spacer(modifier = Modifier.height(8.dp))

        Text(
            text = mod.description,
            style = MaterialTheme.typography.bodyMedium,
            color = MaterialTheme.colorScheme.onSurfaceVariant,
            maxLines = 3,
            overflow = TextOverflow.Ellipsis
        )

        Spacer(modifier = Modifier.height(16.dp))

        // 元数据
        Row(
            modifier = Modifier.fillMaxWidth(),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.Bottom
        ) {
            Column(verticalArrangement = Arrangement.spacedBy(4.dp)) {
                MetadataItem(icon = Icons.Outlined.Info, text = "版本 ${mod.version}")
                if (sort == "stars") {
                    MetadataItem(icon = Icons.Filled.Star, text = "${mod.stars} 星")
                } else {
                    MetadataItem(icon = Icons.Filled.Download, text = "${mod.downloaded_time} 次下载")
                }
                MetadataItem(icon = Icons.Outlined.History, text = "更新于: ${mod.updated_at}")
            }

            Box(
                modifier = Modifier.size(48.dp), // 给一个固定大小，避免UI跳动
                contentAlignment = Alignment.Center
            ) {
                // NEW: The `when` block is expanded to handle the new Updatable and Installed states.
                when (downloadState) {
                    is DownloadState.Downloading -> {
                        CircularProgressIndicator(
                            modifier = Modifier.size(24.dp)
                        )
                    }

                    is DownloadState.Updatable -> {
                        IconButton(
                            onClick = { onInstallClick(mod) },
                            modifier = Modifier.background(
                                color = FloatingActionButtonDefaults.containerColor,
                                shape = FloatingActionButtonDefaults.extendedFabShape,
                            )
                        ) {
                            Icon(Icons.Filled.Update, contentDescription = "更新")
                        }
                    }

                    is DownloadState.Installed -> {
                        // NEW: Show a persistent "Installed" icon if the mod is up-to-date.
                        Icon(
                            imageVector = Icons.Filled.Check,
                            contentDescription = "已安装",
                            tint = MaterialTheme.colorScheme.primary,
                        )
                    }

                    is DownloadState.Success -> {
                        // This can be a transient state right after a download finishes.
                        Icon(
                            imageVector = Icons.Filled.Check,
                            contentDescription = "下载成功",
                            tint = MaterialTheme.colorScheme.primary,
                        )
                    }

                    else -> {
                        // 默认状态 (Idle) 或失败状态 (Error)，显示下载按钮
                        IconButton(
                            onClick = { onInstallClick(mod) },
                            modifier = Modifier.background(
                                color = FloatingActionButtonDefaults.containerColor,
                                shape = FloatingActionButtonDefaults.extendedFabShape,
                            )
                        ) {
                            Icon(Icons.Filled.Download, contentDescription = "下载")
                        }
                    }
                }
            }
        }
    }
}

@Composable
private fun AuthorInfo(
    avatarUrl: String,
    author: String,
    repoUrl: String,
    modifier: Modifier = Modifier
) {
    val context = LocalContext.current

    Row(
        verticalAlignment = Alignment.CenterVertically,
        modifier = modifier.fillMaxWidth()
    ) {
        AsyncImage(
            model = avatarUrl,
            contentDescription = "$author 的头像",
            modifier = Modifier
                .size(48.dp)
                .clip(CircleShape)
                .border(2.dp, MaterialTheme.colorScheme.primary, CircleShape)
        )

        Spacer(modifier = Modifier.width(12.dp))

        Column(modifier = Modifier.weight(1f)) {
            Row {
                Text(
                    text = author,
                    style = MaterialTheme.typography.titleLarge,
                    fontWeight = FontWeight.SemiBold,
                    maxLines = 1,
                    modifier = modifier
                        .weight(1f)
                        .basicMarquee(repeatDelayMillis = 1, iterations = Int.MAX_VALUE)
                )
            }

            Row(
                verticalAlignment = Alignment.CenterVertically,
                modifier = Modifier
                    .clickable {
                        context.startNetUri(repoUrl)
                    }
                    .padding(vertical = 4.dp)
            ) {
                Icon(
                    imageVector = Icons.Filled.Link,
                    contentDescription = "仓库链接",
                    modifier = Modifier.size(14.dp),
                    tint = MaterialTheme.colorScheme.secondary
                )
                Spacer(modifier = Modifier.width(4.dp))
                Text(
                    text = repoUrl,
                    style = MaterialTheme.typography.bodySmall,
                    color = MaterialTheme.colorScheme.secondary,
                    maxLines = 1,
                    overflow = TextOverflow.Ellipsis,
                )
            }
        }
    }
}

@Composable
fun MetadataItem(
    icon: androidx.compose.ui.graphics.vector.ImageVector,
    text: String,
    modifier: Modifier = Modifier,
    onClick: () -> Unit = {}
) {
    Row(
        verticalAlignment = Alignment.CenterVertically,
        modifier = modifier
    ) {
        Icon(
            imageVector = icon,
            contentDescription = null,
            modifier = Modifier.size(16.dp),
            tint = MaterialTheme.colorScheme.onSurfaceVariant
        )
        Spacer(modifier = Modifier.width(8.dp))
        Text(
            text = text,
            style = MaterialTheme.typography.bodySmall,
            color = MaterialTheme.colorScheme.onSurfaceVariant,
            maxLines = 1,
            overflow = TextOverflow.Ellipsis,
            modifier = modifier.clickable { onClick() }
        )
    }
}

@Composable
private fun ModListContent(
    uiState: UiState<ModListState>,
    downloadStates: Map<String, DownloadState>, // 接收状态Map
    onLoadMore: () -> Unit,
    onRetry: () -> Unit,
    onInstallClick: (DownloadInfo) -> Unit,
    sort: String,
) {
    Box(modifier = Modifier
        .fillMaxSize()
        .windowInsetsPadding(WindowInsets.navigationBars)) {
        when (uiState) {
            is UiState.Loading -> {
                Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
                    CircularProgressIndicator()
                }
            }

            is UiState.Success -> {
                val modListState = uiState.data
                val mods = modListState.mods

                if (mods.isEmpty() && !modListState.hasMore) {
                    Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
                        Text("什么也没找到")
                    }
                    return@Box
                }

                LazyColumn(
                    modifier = Modifier.fillMaxWidth(),
                    contentPadding = PaddingValues(
                        top = 10.dp,
                        start = 10.dp,
                        end = 10.dp,
                        bottom = 125.dp
                    ),
                    verticalArrangement = Arrangement.spacedBy(10.dp)
                ) {
                    items(mods.size) { index ->
                        if (index >= mods.size - 5 && modListState.hasMore && !modListState.isLoadingMore) {
                            LaunchedEffect(Unit) {
                                onLoadMore()
                            }
                        }

                        val mod = mods[index]
                        // 4. 为每个模组查找其对应的下载状态，如果不存在则默认为 Idle
                        val downloadState = downloadStates[mod.id] ?: DownloadState.Idle

                        EnhancedModShopCard(
                            mod = mod,
                            sort = sort,
                            downloadState = downloadState, // 将具体状态传递给卡片
                            onInstallClick = onInstallClick
                        )
                    }

                    if (modListState.isLoadingMore) {
                        item {
                            Box(
                                modifier = Modifier
                                    .fillMaxWidth()
                                    .padding(16.dp),
                                contentAlignment = Alignment.Center
                            ) {
                                CircularProgressIndicator()
                            }
                        }
                    }
                }
            }

            is UiState.Error -> {
                Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
                    Column(horizontalAlignment = Alignment.CenterHorizontally) {
                        Log.e("HJR", "error: ${uiState.message}")
                        Text(text = uiState.message)
                        Spacer(Modifier.height(8.dp))
                        Button(onClick = onRetry) {
                            Text("重试")
                        }
                    }
                }
            }
        }
    }
}