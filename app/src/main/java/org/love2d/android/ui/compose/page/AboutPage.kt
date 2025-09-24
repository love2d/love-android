package org.love2d.android.ui.compose.page

import android.content.Intent
import android.util.Log
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.KeyboardArrowRight
import androidx.compose.material.icons.outlined.Groups
import androidx.compose.material.icons.outlined.Info
import androidx.compose.material.icons.outlined.Link
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.core.net.toUri
import org.love2d.android.executable.R
import org.love2d.android.util.startNetUri
import java.io.File


/**
 * ClassName AboutPage
 * Description
 * Create by hjr
 * Date 2025/6/27 17:26
 */
@Composable
fun AboutScreen_Scrollable() {
    val context = LocalContext.current

    val file = File(context.getExternalFilesDir(null), "save/love/Balator-LOVE")
    file.listFiles()?.forEach {
        Log.e("HJR", "filesDir: ${it.name}")
    }

    // 将 LazyColumn作为根布局，使其可滚动整个页面
    LazyColumn(
        modifier = Modifier
            .fillMaxSize()
            .background(MaterialTheme.colorScheme.surface),
        contentPadding = PaddingValues(bottom = 16.dp), // 仅保留底部padding
        horizontalAlignment = Alignment.CenterHorizontally // 让所有子项内容居中
    ) {
        // --- 1. 将原先的顶部品牌区，作为列表的第一个 item ---
        item {
            Column(
                modifier = Modifier
                    .fillMaxWidth()
                    .padding(top = 48.dp, bottom = 24.dp, start = 16.dp, end = 16.dp),
                horizontalAlignment = Alignment.CenterHorizontally,
                verticalArrangement = Arrangement.spacedBy(16.dp)
            ) {
                Image(
                    painter = painterResource(id = R.drawable.icon),
                    contentDescription = "App Icon",
                    modifier = Modifier
                        .size(120.dp)
                        .clip(RoundedCornerShape(28.dp))
                )
                val appName = context.applicationInfo.loadLabel(context.packageManager).toString()
                Text(
                    text = appName,
                    style = MaterialTheme.typography.headlineSmall,
                    fontWeight = FontWeight.Bold
                )
                val versionName = context.packageManager.getPackageInfo(context.packageName, 0).versionName
                Text(
                    text = "版本 $versionName",
                    style = MaterialTheme.typography.bodyMedium,
                    color = MaterialTheme.colorScheme.onSurfaceVariant
                )
            }
        }

        // --- 2. 列表信息区，内容保持不变 ---
        item {
            Column(
                modifier = Modifier.padding(horizontal = 16.dp),
                verticalArrangement = Arrangement.spacedBy(8.dp)
            ) {
                SectionHeader("关于项目")
                EnhancedAboutCard(
                    icon = Icons.Outlined.Info,
                    title = "项目介绍",
                    content = "基于Love2D引擎，使用lovely-injector实现模组化。",
                    isShowArrow = false,
                    onClick = {}
                )
            }
        }

        item {
            Column(
                modifier = Modifier.padding(horizontal = 16.dp),
                verticalArrangement = Arrangement.spacedBy(8.dp)
            ) {
                SectionHeader("核心依赖")
                EnhancedAboutCard(
                    icon = Icons.Outlined.Link,
                    title = "Love2D 官方",
                    content = "强大的2D游戏开发框架。",
                    onClick = {
                        context.startNetUri("https://github.com/love2d/love")
                    }
                )
                EnhancedAboutCard(
                    icon = Icons.Outlined.Link,
                    title = "Lovely Injector",
                    content = "为LÖVE提供运行时代码注入。",
                    onClick = {
                        context.startNetUri("https://github.com/ethangreen-dev/lovely-injector")
                    }
                )
            }
        }

        item {
            Column(
                modifier = Modifier.padding(horizontal = 16.dp),
                verticalArrangement = Arrangement.spacedBy(8.dp)
            ) {
                SectionHeader("社区")
                EnhancedAboutCard(
                    icon = Icons.Outlined.Groups,
                    title = "加入手机版交流群",
                    content = "点击加入移动端APP交流群。",
                    onClick = {
                        val intent = Intent().apply {
                            data =
                                "mqqopensdkapi://bizAgent/qm/qr?url=http%3A%2F%2Fqm.qq.com%2Fcgi-bin%2Fqm%2Fqr%3Ffrom%3Dapp%26p%3Dandroid%26jump_from%3Dwebapi%26k%3DMPjUV66Q5iyXzPxoCFK6F5jlCwKHu4z_".toUri()
                            flags = Intent.FLAG_ACTIVITY_NEW_TASK
                        }
                        context.startActivity(intent)
                    }
                )
                EnhancedAboutCard(
                    icon = Icons.Outlined.Groups,
                    title = "加入PC版交流群",
                    content = "点击加入小丑牌玩家交流群。",
                    onClick = {
                        val intent = Intent().apply {
                            data =
                                "mqqopensdkapi://bizAgent/qm/qr?url=http%3A%2F%2Fqm.qq.com%2Fcgi-bin%2Fqm%2Fqr%3Ffrom%3Dapp%26p%3Dandroid%26jump_from%3Dwebapi%26k%3D${"mqX9JdB5bNZkPNr-8AnFIfCBXQcmBH4O"}".toUri()
                            flags = Intent.FLAG_ACTIVITY_NEW_TASK
                        }
                        context.startActivity(intent)
                    }
                )
            }
        }
    }
}

@Composable
fun EnhancedAboutCard(
    icon: ImageVector,
    title: String,
    content: String,
    isShowArrow: Boolean = true,
    onClick: () -> Unit,
) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(16.dp))
            .background(MaterialTheme.colorScheme.surfaceContainer)
            .clickable(onClick = onClick)
            .padding(horizontal = 16.dp, vertical = 20.dp),
        verticalAlignment = Alignment.CenterVertically,
        horizontalArrangement = Arrangement.spacedBy(16.dp)
    ) {
        // 左侧图标
        Icon(
            imageVector = icon,
            contentDescription = title,
            modifier = Modifier.size(24.dp),
            tint = MaterialTheme.colorScheme.primary
        )
        // 中间文字
        Column(modifier = Modifier.weight(1f)) {
            Text(
                text = title,
                style = MaterialTheme.typography.titleMedium,
                fontWeight = FontWeight.SemiBold
            )
            Spacer(modifier = Modifier.height(4.dp))
            Text(
                text = content,
                style = MaterialTheme.typography.bodyMedium,
                color = MaterialTheme.colorScheme.onSurfaceVariant
            )
        }
        // 右侧箭头，作为可点击的视觉提示
        if (isShowArrow) {
            Icon(
                imageVector = Icons.AutoMirrored.Filled.KeyboardArrowRight,
                contentDescription = null,
                tint = MaterialTheme.colorScheme.onSurfaceVariant.copy(alpha = 0.6f)
            )
        }
    }
}

@Composable
fun SectionHeader(title: String, modifier: Modifier = Modifier) {
    Text(
        text = title,
        style = MaterialTheme.typography.titleSmall,
        color = MaterialTheme.colorScheme.primary,
        modifier = modifier
            .padding(horizontal = 16.dp, vertical = 8.dp)
    )
}