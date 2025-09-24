package org.love2d.android.ui.compose.page

import android.app.Activity
import androidx.compose.foundation.background
import androidx.compose.foundation.basicMarquee
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.CalendarToday
import androidx.compose.material.icons.filled.Cloud
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.Link
import androidx.compose.material.icons.filled.PhoneAndroid
import androidx.compose.material.icons.filled.ShoppingBasket
import androidx.compose.material.icons.filled.Source
import androidx.compose.material3.ExtendedFloatingActionButton
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import org.love2d.android.room.mod.ModInfo
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.compose.EmptyLottie
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.startNetUri

/**
 * ClassName ModListPage
 * Description
 * Create by hjr
 * Date 2025/6/25 14:20
 */
@Composable
fun EnhancedModListPage(
    localActivity: Activity,
    modPath: String,
    viewModel: GameManagerViewModel, // 假设的 ViewModel
    modDelete: (ModInfo) -> Unit,
) {
    val modsFlow = remember(modPath) { viewModel.getPathMods(modPath) }
    val modList by modsFlow.collectAsState(initial = emptyList())

    Box(modifier = Modifier.fillMaxSize()) {
        if (modList.isEmpty()) {
            // --- 空状态 ---
            Box(
                modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center
            ) {
                // EmptyLottie 是您自定义的组件，这里保持原样
                EmptyLottie(emptyText = "暂未添加模组") {
                    FileSelectorUtil.openFilePicker(localActivity, FileSelectorUtil.REQUEST_MOD_CODE_FILE)
                }
            }
        } else {
            // --- 列表状态 ---
            LazyColumn(
                modifier = Modifier.fillMaxWidth(), contentPadding = PaddingValues(
                    top = 10.dp,
                    start = 10.dp,
                    end = 10.dp,
                    bottom = 125.dp
                ), verticalArrangement = Arrangement.spacedBy(10.dp)
            ) {
                items(modList.size) { index ->
                    EnhancedModCard(
                        modInfo = modList[index], onDelete = modDelete
                    )
                }
            }
        }

        if (modList.isNotEmpty()) {
            // --- 悬浮操作按钮 ---
            ExtendedFloatingActionButton(onClick = {
                FileSelectorUtil.openFilePicker(localActivity, FileSelectorUtil.REQUEST_MOD_CODE_FILE)
            },
                modifier = Modifier
                    .align(Alignment.BottomEnd)
                    .padding(16.dp),
                icon = { Icon(Icons.Default.Add, contentDescription = "添加模组") },
                text = { Text("从本地安装") })
        }
    }
}

@Composable
fun EnhancedModCard(
    modInfo: ModInfo,
    onDelete: (ModInfo) -> Unit,
) {
    val context = LocalContext.current
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .background(MaterialTheme.colorScheme.surfaceContainer, RoundedCornerShape(24.dp))
            .padding(20.dp)
    ) {
        // --- 顶部区域重构：实现标题与按钮的精确居中 ---

        // 1. 新增一个 Row 专门用于放置标题和删除按钮
        Row(
            modifier = Modifier.fillMaxWidth(), verticalAlignment = Alignment.CenterVertically // 👈 关键：设置为垂直居中对齐
        ) {
            // 左侧：仅有标题
            Text(
                text = modInfo.name,
                style = MaterialTheme.typography.headlineSmall,
                fontWeight = FontWeight.Bold,
                maxLines = 1,
                modifier = Modifier
                    .weight(1f) // 👈 关键：让标题占据所有可用空间，将按钮推到最右侧
                    .padding(end = 16.dp) // 在标题和按钮间留出一些间距
                    .basicMarquee(repeatDelayMillis = 1, iterations = Int.MAX_VALUE)
            )
            // 右侧：删除按钮
            IconButton(onClick = { onDelete(modInfo) }) {
                Icon(Icons.Default.Delete, contentDescription = "删除模组")
            }
        }

        // 2. 作者信息现在位于上方 Row 的下方
        Spacer(modifier = Modifier.height(4.dp))
        Text(
            text = "作者: ${modInfo.author}",
            style = MaterialTheme.typography.titleMedium,
            color = MaterialTheme.colorScheme.onSurfaceVariant,
            // 为了对齐，可以给作者信息也加上一点左内边距，使其与标题对齐
            // 如果您的 MaterialTheme 版本较新，标题默认可能没有内边距，这一行则非必须
            // modifier = Modifier.padding(start = 4.dp)
        )

        Spacer(modifier = Modifier.height(16.dp))
        HorizontalDivider(thickness = 1.dp, color = MaterialTheme.colorScheme.outlineVariant.copy(alpha = 0.5f))
        Spacer(modifier = Modifier.height(16.dp))


        // --- 底部区域：元数据 (保持不变) ---
        Column(verticalArrangement = Arrangement.spacedBy(8.dp)) {
            MetadataItem(
                icon = if (modInfo.isLocal) Icons.Default.Source else Icons.Default.ShoppingBasket, text = "来源: ${modInfo.from}"
            )
            if (!modInfo.isLocal) {
                MetadataItem(
                    icon = Icons.Filled.Link, text = "下载地址: ${modInfo.github_repo_url}"
                ) {
                    context.startNetUri(modInfo.github_repo_url)
                }
            }
            MetadataItem(
                icon = if (modInfo.isLocal) Icons.Default.PhoneAndroid else Icons.Default.Cloud,
                text = if (modInfo.isLocal) "本地安装" else "网络来源"
            )
            MetadataItem(
                icon = Icons.Default.CalendarToday, text = "安装于: ${modInfo.created_at}"
            )
        }
    }
}