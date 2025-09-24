package org.love2d.android.ui.compose.page

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
import androidx.compose.material.icons.filled.Error
import androidx.compose.material.icons.filled.InstallMobile
import androidx.compose.material.icons.filled.Link
import androidx.compose.material.icons.filled.Star
import androidx.compose.material.icons.outlined.History
import androidx.compose.material.icons.outlined.Info
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
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import coil.compose.AsyncImage
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import org.love2d.android.room.download.DownloadInfo
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.startNetUri
import java.io.File

/**
 * ClassName ModShopPage
 * Description
 * Create by hjr
 * Date 2025/7/1 16:10
 */

@Composable
fun DownloadModShopPage(viewModel: GameManagerViewModel, query: String, sort: String) {
    val context = LocalContext.current
    var isInitialLoading by remember { mutableStateOf(true) }
    var isLoading by remember { mutableStateOf(true) }
    val gameInfo by viewModel.currentGame.collectAsState()

    // 使用 remember 来在重组之间保持 StateFlow 实例
    val _installStates = remember { MutableStateFlow<Map<String, InstallState>>(emptyMap()) }
    val installStates: StateFlow<Map<String, InstallState>> = _installStates.asStateFlow()
    val uiInstallState = installStates.collectAsState()

    val currentDownloadFlow = remember(sort, query) {
        when {
            query.isNotBlank() -> viewModel.searchByNameDownloadInfo(query)
            sort == "stars" -> viewModel.getAllByStarsDesc()
            else -> viewModel.getAllByDownloadTimeDesc()
        }
    }

    val modPath = gameInfo!!.modPath
    val mods by currentDownloadFlow.collectAsState()
    // 1. 获取一个协程作用域
    val scope = rememberCoroutineScope()

    // 初始化安装状态
    LaunchedEffect(mods) {
        isLoading = true
        // 创建一个临时的 map 来构建初始状态
        val initialStateMap = mutableMapOf<String, InstallState>()
        mods.forEach { mod ->
            mod.installPath = modPath
            val existsModByModId = viewModel.existsModByModId(modPath, mod.id)
            if (existsModByModId) {
                // 如果已安装，直接在我们的状态地图中标记为 Success
                initialStateMap[mod.id] = InstallState.Success
            } else {
                // 否则，标记为 Idle
                initialStateMap[mod.id] = InstallState.Idle
            }
        }
        // 一次性更新整个状态地图
        _installStates.update { initialStateMap }

        isLoading = false
        if (isInitialLoading) {
            isInitialLoading = false
        }
    }

    if (isLoading && isInitialLoading) {
        // 显示加载动画
        Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
            CircularProgressIndicator()
        }
    } else {
        DownloadInfoModListContent(
            mods = mods, onInstallClick = { mod ->
                scope.launch {
                    _installStates.update { it + (mod.id to InstallState.Installing) }
                    withContext(Dispatchers.IO) {
                        val zipFile = File(mod.file_path)
                        val resultName = FileSelectorUtil.installZipFileToModPathNoInsert(context, modPath, zipFile)
                        viewModel.insertNetMod(mod, resultName)
                    }
                    // 修改状态
                    _installStates.update { it + (mod.id to InstallState.Success) }
                }
            }, sort = sort, installStates = uiInstallState.value, onDeleteMod = { deleteMod ->
                scope.launch {
                    viewModel.deleteNetMod(deleteMod)
                }
            }
        )
    }
}

@Composable
fun LocalEnhancedModShopCard(
    mod: DownloadInfo,
    sort: String,
    onInstallClick: (DownloadInfo) -> Unit,
    onDeleteMod: (DownloadInfo) -> Unit,
    modifier: Modifier = Modifier,
    installState: InstallState,
) {
    Column(
        modifier = modifier
            .fillMaxWidth()
            .background(MaterialTheme.colorScheme.surfaceContainer, RoundedCornerShape(24.dp))
            .padding(16.dp)
    ) {
        // 作者信息
        AuthorInfo(
            avatarUrl = mod.author_avatar_url, author = mod.author, repoUrl = mod.github_repo_url, deleteMod = {
                onDeleteMod(mod)
            }
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
                when (installState) {
                    is InstallState.Idle -> {
                        IconButton(
                            onClick = { onInstallClick(mod) }, modifier = Modifier.background(
                                color = FloatingActionButtonDefaults.containerColor,
                                shape = FloatingActionButtonDefaults.extendedFabShape,
                            )
                        ) {
                            Icon(Icons.Filled.InstallMobile, contentDescription = "安装")
                        }
                    }

                    is InstallState.Installing -> {
                        CircularProgressIndicator(
                            modifier = Modifier.size(24.dp), color = MaterialTheme.colorScheme.primary
                        )
                    }

                    is InstallState.Success -> {
                        Icon(
                            imageVector = Icons.Filled.Check,
                            contentDescription = "安装成功",
                            tint = MaterialTheme.colorScheme.primary
                        )
                    }

                    is InstallState.Error -> {
                        Icon(
                            imageVector = Icons.Filled.Error,
                            contentDescription = "安装失败",
                            tint = MaterialTheme.colorScheme.error
                        )
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
    deleteMod: () -> Unit,
    modifier: Modifier = Modifier,
) {
    val context = LocalContext.current

    Row(
        verticalAlignment = Alignment.CenterVertically, modifier = modifier.fillMaxWidth()
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
                Icon(
                    imageVector = Icons.Filled.Delete,
                    contentDescription = "删除",
                    modifier = Modifier
                        .padding(start = 8.dp)
                        .size(24.dp)
                        .clickable { deleteMod() }
                )
            }

            Row(verticalAlignment = Alignment.CenterVertically, modifier = Modifier
                .clickable {
                    context.startNetUri(repoUrl)
                }
                .padding(vertical = 4.dp)) {
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
private fun DownloadInfoModListContent(
    mods: List<DownloadInfo>,
    onInstallClick: (DownloadInfo) -> Unit,
    onDeleteMod: (DownloadInfo) -> Unit,
    sort: String,
    installStates: Map<String, InstallState>,
) {
    Box(
        modifier = Modifier
            .fillMaxSize()
            .windowInsetsPadding(WindowInsets.navigationBars)
    ) {
        LazyColumn(
            modifier = Modifier.fillMaxWidth(), contentPadding = PaddingValues(
                top = 10.dp, start = 10.dp, end = 10.dp, bottom = 125.dp
            ), verticalArrangement = Arrangement.spacedBy(10.dp)
        ) {
            items(mods.size) { index ->
                val mod = mods[index]
                // 4. 为每个模组查找其对应的下载状态，如果不存在则默认为 Idle
                val installState = installStates[mod.id] ?: InstallState.Idle
                LocalEnhancedModShopCard(
                    mod = mod,
                    sort = sort,
                    onInstallClick = onInstallClick,
                    installState = installState,
                    onDeleteMod = onDeleteMod
                )
            }
        }
    }
}

// 这个密封类用于表示单个模组的安装状态
sealed class InstallState {
    // 默认状态，未开始或已完成
    data object Idle : InstallState()

    // 正在安装中
    data object Installing : InstallState()

    // 安装成功
    data object Success : InstallState()

    // 安装失败
    data class Error(val message: String) : InstallState()
}

