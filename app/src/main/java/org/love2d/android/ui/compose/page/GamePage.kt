package org.love2d.android.ui.compose.page

import android.graphics.Bitmap
import android.util.Log
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.aspectRatio
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.lazy.grid.items
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Add
import androidx.compose.material.icons.filled.PlayArrow
import androidx.compose.material.icons.filled.Stop
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.FloatingActionButton
import androidx.compose.material3.Icon
import androidx.compose.material3.LargeFloatingActionButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.*
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.ColorFilter
import androidx.compose.ui.graphics.ImageBitmap
import androidx.compose.ui.graphics.Shadow
import androidx.compose.ui.graphics.asImageBitmap
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import org.love2d.android.executable.R
import org.love2d.android.room.game.GameInfo
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.compose.EmptyLottie
import org.love2d.android.util.GameStartUtil

@Composable
fun EnhancedGamePage(
    games: List<GameInfo>,
    addGame: () -> Unit,
    onGameCardClick: (GameInfo) -> Unit,
    onGameStart: (GameInfo) -> Unit,
    viewModel: GameManagerViewModel, // 假设的 ViewModel
    modifier: Modifier = Modifier,
) {
    Box(modifier = modifier.fillMaxSize()) {
        if (games.isEmpty()) {
            // 空状态保持不变
            EmptyLottie(emptyText = "去添加一款游戏吧~", addGame = addGame)
        } else {
            LazyVerticalGrid(
                columns = GridCells.Fixed(2),
                contentPadding = PaddingValues(16.dp),
                verticalArrangement = Arrangement.spacedBy(16.dp),
                horizontalArrangement = Arrangement.spacedBy(16.dp)
            ) {
                items(games, key = { it.id }) { game ->
                    EnhancedGameCard(
                        game = game,
                        onGameStart = onGameStart,
                        onGameCardClick = onGameCardClick
                    )
                }
            }

            // 使用标准的 LargeFloatingActionButton，更符合设计规范
            LargeFloatingActionButton(
                onClick = addGame,
                modifier = Modifier
                    .align(Alignment.BottomEnd)
                    .padding(16.dp),
                shape = RoundedCornerShape(28.dp)
            ) {
                Icon(Icons.Filled.Add, contentDescription = "添加游戏", modifier = Modifier.size(36.dp))
            }
        }
    }
}

@Composable
fun EnhancedGameCard(
    game: GameInfo,
    onGameStart: (GameInfo) -> Unit,
    onGameCardClick: (GameInfo) -> Unit,
) {
    // 直接派生出运行状态，而不是在组件内部使用可变状态
    val currentRunningGame by GameStartUtil.currentRunningGame.collectAsState()
    val isRunning = currentRunningGame?.first == true && currentRunningGame?.second?.id == game.id

    val cardShape = RoundedCornerShape(24.dp)
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .clip(cardShape)
            .background(MaterialTheme.colorScheme.surfaceContainer)
            .clickable { onGameCardClick(game) }
    ) {
        // 游戏图标/横幅
        GameIcon(
            base64Icon = game.iconPath,
            contentDescription = game.name,
            modifier = Modifier
                .fillMaxWidth()
                .aspectRatio(16f / 10f) // 使用比例让图片更协调
        )

        // 底部信息与操作区域
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .padding(12.dp)
        ) {
            Text(
                text = game.name,
                style = MaterialTheme.typography.titleMedium,
                fontWeight = FontWeight.Bold,
                maxLines = 1,
                overflow = TextOverflow.Ellipsis
            )
            Spacer(modifier = Modifier.height(12.dp))

            // 按钮
            Button(
                onClick = { onGameStart(game) },
                modifier = Modifier.fillMaxWidth(),
                colors = if (isRunning) {
                    // 正在运行时显示“停止”按钮，使用危险操作颜色
                    ButtonDefaults.buttonColors(containerColor = MaterialTheme.colorScheme.error)
                } else {
                    ButtonDefaults.filledTonalButtonColors()
                }
            ) {
                Text(text = if (isRunning) "停止运行" else "启动游戏")
            }
        }
    }
}

@Composable
fun GameIcon(base64Icon: String?, contentDescription: String?, modifier: Modifier = Modifier) {
    if (!base64Icon.isNullOrEmpty()) {
        // 使用优化后的异步图片加载组件
        AsyncBase64Image(base64Icon, contentDescription, modifier)
    } else {
        // 默认占位图
        Box(modifier = modifier, contentAlignment = Alignment.Center) {
            Image(
                painter = painterResource(id = R.drawable.baseline_videogame_asset_24),
                contentDescription = contentDescription,
                modifier = Modifier.size(128.dp),
                colorFilter = ColorFilter.tint(MaterialTheme.colorScheme.primary)
            )
        }
    }
}

@Composable
fun AsyncBase64Image(base64Str: String, contentDescription: String?, modifier: Modifier = Modifier) {
    var imageBitmap by remember(base64Str) { mutableStateOf<Bitmap?>(null) }

    // LaunchedEffect 会在 key (base64Str) 变化时启动一个协程
    LaunchedEffect(base64Str) {
        // 切换到 IO 线程池执行耗时的解码操作
        imageBitmap = withContext(Dispatchers.IO) {
            try {
                val pureBase64 = base64Str.substringAfter(",")
                val imageBytes = android.util.Base64.decode(pureBase64, android.util.Base64.DEFAULT)
                android.graphics.BitmapFactory.decodeByteArray(imageBytes, 0, imageBytes.size)
            } catch (e: Exception) {
                Log.e("AsyncBase64Image", "Failed to decode Base64 string", e)
                null
            }
        }
    }

    if (imageBitmap != null) {
        Image(
            bitmap = imageBitmap!!.asImageBitmap(),
            contentDescription = contentDescription,
            modifier = modifier,
            contentScale = ContentScale.Crop
        )
    } else {
        // 在图片加载完成前，显示一个占位符
        Box(modifier = modifier.background(MaterialTheme.colorScheme.surfaceContainerHighest))
    }
}

@Composable
fun Base64Image(base64Str: String, contentDescription: String?, modifier: Modifier = Modifier) {
    val pureBase64 = base64Str.substringAfter(",") // 如果有前缀，去掉它
    val imageBytes = android.util.Base64.decode(pureBase64, android.util.Base64.DEFAULT)
    val bitmap = android.graphics.BitmapFactory.decodeByteArray(imageBytes, 0, imageBytes.size)
    if (bitmap != null) {
        Image(
            bitmap = bitmap.asImageBitmap(),
            contentDescription = contentDescription,
            modifier,
            contentScale = ContentScale.Crop
        )
    }
}

@Composable
fun EnhancedGamePage_SingleColumn(
    games: List<GameInfo>,
    addGame: () -> Unit,
    onGameCardClick: (GameInfo) -> Unit,
    onGameStart: (GameInfo) -> Unit,
    viewModel: GameManagerViewModel, // 假设的 ViewModel
    modifier: Modifier = Modifier,
) {
    Box(modifier = modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
        if (games.isEmpty()) {
            EmptyLottie(emptyText = "去添加一款游戏吧~", addGame = addGame)
        } else {
            // 将 Grid 改为 LazyColumn
            LazyColumn(
                modifier = Modifier.fillMaxSize(),
                contentPadding = PaddingValues(16.dp),
                verticalArrangement = Arrangement.spacedBy(16.dp)
            ) {
                items(games.size) { index ->
                    ImmersiveGameCard( // 使用全新的沉浸式卡片
                        game = games[index],
                        onGameStart = onGameStart,
                        onGameCardClick = onGameCardClick
                    )
                }
            }

            FloatingActionButton(
                onClick = addGame,
                modifier = Modifier
                    .align(Alignment.BottomEnd)
                    .padding(16.dp),
            ) {
                Icon(Icons.Filled.Add, contentDescription = "添加游戏")
            }
        }
    }
}

@Composable
fun ImmersiveGameCard(
    game: GameInfo,
    onGameStart: (GameInfo) -> Unit,
    onGameCardClick: (GameInfo) -> Unit
) {
    val currentRunningGame by GameStartUtil.currentRunningGame.collectAsState()
    val isRunning = currentRunningGame?.first == true && currentRunningGame?.second?.id == game.id


    // 使用 Box 实现叠加布局
    Box(
        modifier = Modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(24.dp)) // ✅ 关键：确保水波纹也跟着圆角走
            .background(MaterialTheme.colorScheme.surfaceContainer)
            .clickable { onGameCardClick(game) }
    ) {
        // --- 1. 背景层：游戏图片 ---
        GameIcon(
            base64Icon = game.iconPath,
            contentDescription = game.name,
            modifier = Modifier
                .fillMaxWidth()
                .aspectRatio(16f / 9f), // 16:9 黄金比例，更像游戏横幅
        )

        // --- 2. 遮罩层：从下至上的黑色半透明渐变，确保文字清晰可读 ---
        Box(
            modifier = Modifier
                .fillMaxSize()
                .background(
                    Brush.verticalGradient(
                        colors = listOf(Color.Transparent, Color.Black.copy(alpha = 0.8f)),
                        startY = 400f // 从中间靠下的位置开始渐变
                    )
                )
        )

        // --- 3. 前景层：游戏标题（左下角） ---
        Text(
            text = game.name,
            style = MaterialTheme.typography.headlineSmall.copy(
                color = Color.White, // 使用白色文字以保证对比度
                letterSpacing = 1.sp,
                shadow = Shadow(color = Color.Black.copy(alpha = 0.7f), blurRadius = 8f) // 文字阴影
            ),
            fontWeight = FontWeight.Bold,
            maxLines = 2,
            overflow = TextOverflow.Ellipsis,
            modifier = Modifier
                .align(Alignment.BottomStart)
                .padding(20.dp)
                .fillMaxWidth(0.7f) // 标题最宽占70%，避免与按钮重叠
        )

        // --- 4. 操作层：启动/停止悬浮按钮（右下角） ---
        FloatingActionButton(
            onClick = { onGameStart(game) },
            modifier = Modifier
                .align(Alignment.BottomEnd)
                .padding(16.dp),
            shape = CircleShape,
            containerColor = if (isRunning) MaterialTheme.colorScheme.errorContainer else MaterialTheme.colorScheme.primaryContainer,
            contentColor = if (isRunning) MaterialTheme.colorScheme.onErrorContainer else MaterialTheme.colorScheme.onPrimaryContainer
        ) {
            Icon(
                imageVector = if (isRunning) Icons.Default.Stop else Icons.Default.PlayArrow,
                contentDescription = if (isRunning) "停止游戏" else "启动游戏"
            )
        }
    }
}
