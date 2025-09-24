package org.love2d.android.ui.compose.page

import android.content.Intent
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
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
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Check
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.outlined.Info
import androidx.compose.material.icons.outlined.Link
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.OutlinedButton
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.core.net.toUri
import org.love2d.android.bean.LocalModManifestBean
import org.love2d.android.room.game.GameInfo
import org.love2d.android.room.mod.ModInfo
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.startNetUri

@Composable
fun LocalModPage(game: GameInfo, viewModel: GameManagerViewModel, installMod: (ModInfo) -> Unit) {
    val context = LocalContext.current
    val modItems = viewModel.getBuiltInModState(game.modPath, context).collectAsState()

    Box(modifier = Modifier.fillMaxSize()) {
        LazyColumn(
            modifier = Modifier.fillMaxWidth(),  contentPadding = PaddingValues(
                top = 10.dp,
                start = 10.dp,
                end = 10.dp,
                bottom = 125.dp
            ), verticalArrangement = Arrangement.spacedBy(10.dp)
        ) {
            items(modItems.value.size) { index ->
                EnhancedLocalModItem(item = modItems.value[index], onDelete = {
                    viewModel.deleteMod(modItems.value[index].modInfo!!)
                }, onInstall = {
                    FileSelectorUtil.installZipFromAssetsToModPath(context, game.modPath, modItems.value[index].fileName)
                })
            }
        }
    }
}

@Composable
fun EnhancedLocalModItem(
    item: LocalModManifestBean,
    onDelete: (LocalModManifestBean) -> Unit,
    onInstall: (LocalModManifestBean) -> Unit,
    modifier: Modifier = Modifier,
) {
    val context = LocalContext.current
    Column(
        modifier = modifier
            .fillMaxWidth()
            .background(MaterialTheme.colorScheme.surfaceContainer, RoundedCornerShape(24.dp))
            .padding(20.dp) // 使用稍大的内边距
    ) {
        // --- 主要信息 ---
        Text(
            text = item.name,
            style = MaterialTheme.typography.headlineSmall,
            fontWeight = FontWeight.Bold,
            color = MaterialTheme.colorScheme.onSurface
        )

        Spacer(modifier = Modifier.height(8.dp))

        Text(
            text = item.description,
            style = MaterialTheme.typography.bodyMedium,
            color = MaterialTheme.colorScheme.onSurfaceVariant,
            maxLines = 3,
            overflow = TextOverflow.Ellipsis
        )

        Spacer(modifier = Modifier.height(16.dp))

        // --- 元数据 ---
        // 使用与上个组件相同的 MetadataItem 辅助组件来保持风格统一
        MetadataItem(icon = Icons.Outlined.Info, text = "版本 ${item.version_number}")
        Spacer(modifier = Modifier.height(6.dp))
        MetadataItem(icon = Icons.Outlined.Link, text = "来源: ${item.website_url}", onClick = {
            context.startNetUri(item.website_url)
        })

        Spacer(modifier = Modifier.height(20.dp))

        // --- 操作按钮 ---
        Row(
            modifier = Modifier.fillMaxWidth(),
            horizontalArrangement = Arrangement.End,
            verticalAlignment = Alignment.CenterVertically
        ) {
            // 根据是否已安装，显示不同的按钮组合
            if (item.isInstall) {
                // 已安装，显示“卸载”按钮，使用危险操作的视觉提示（红色）
                OutlinedButton(
                    onClick = { onDelete(item) },
                    colors = ButtonDefaults.outlinedButtonColors(
                        contentColor = MaterialTheme.colorScheme.error
                    ),
                    border = BorderStroke(1.dp, MaterialTheme.colorScheme.error)
                ) {
                    Icon(Icons.Default.Delete, contentDescription = "卸载", modifier = Modifier.size(ButtonDefaults.IconSize))
                    Spacer(modifier = Modifier.width(ButtonDefaults.IconSpacing))
                    Text("卸载模组")
                }
            } else {
                // 未安装，显示“启用”按钮，作为主要操作
                Button(onClick = { onInstall(item) }) {
                    Icon(Icons.Default.Check, contentDescription = "启用", modifier = Modifier.size(ButtonDefaults.IconSize))
                    Spacer(modifier = Modifier.width(ButtonDefaults.IconSpacing))
                    Text("启用模组")
                }
            }
        }
    }
}
