package org.love2d.android.ui.compose.page

import android.app.Activity
import android.util.Log
import androidx.compose.foundation.background
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
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.safeDrawing
import androidx.compose.foundation.layout.windowInsetsPadding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ArrowBack
import androidx.compose.material.icons.automirrored.filled.KeyboardArrowRight
import androidx.compose.material.icons.filled.Book
import androidx.compose.material.icons.filled.BugReport
import androidx.compose.material.icons.filled.CalendarToday
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.Edit
import androidx.compose.material.icons.filled.Extension
import androidx.compose.material.icons.filled.History
import androidx.compose.material.icons.filled.PlayArrow
import androidx.compose.material.icons.filled.ShoppingBasket
import androidx.compose.material.icons.filled.Stop
import androidx.compose.material.icons.filled.ToggleOff
import androidx.compose.material.icons.filled.ToggleOn
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.ExtendedFloatingActionButton
import androidx.compose.material3.FabPosition
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Surface
import androidx.compose.material3.Switch
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.scale
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.activity.Screen
import org.love2d.android.ui.compose.ConfirmDialog
import org.love2d.android.ui.compose.GameNameInputDialog
import org.love2d.android.ui.compose.GameRunningTipDialog
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.GameStartUtil
import org.love2d.android.util.TimeUtil

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun GameDetailPage(
    viewModel: GameManagerViewModel,
    navController: NavController,
    localActivity : Activity
) {
    val context = LocalContext.current

    // --- 状态管理：完全保留您原有的所有状态逻辑 ---
    val gameInfo by viewModel.currentGame.collectAsState()

    //是否展示输入游戏名称弹窗
    val isShowGameNameInput by viewModel.isShowGameNameInput.collectAsState()
    var gameName by remember(gameInfo?.name) { mutableStateOf(gameInfo?.name ?: "") }

    //判断是否是当前游戏正在运行
    val isRunningGameInfo by GameStartUtil.currentRunningGame.collectAsState()
    val isThisGameRunning = isRunningGameInfo?.first == true && isRunningGameInfo?.second?.id == gameInfo?.id

    //游戏运行弹窗
    val isShowRunGameTipDialog by viewModel.isShowRunGameTipDialog.collectAsState()

    //二次确认弹窗
    val isShowFxDialog by viewModel.isShowFxDialog.collectAsState()

    //是否禁用mod 默认不开启
    var isEnableMod by remember { mutableStateOf(!gameInfo?.isEnableMod!!) }

    //获取一个携程
    val scope = rememberCoroutineScope()

    Surface(
        modifier = Modifier.fillMaxSize(),
        color = MaterialTheme.colorScheme.background,
    ) {
        // 使用 Scaffold 构建页面基本结构
        Scaffold(
            modifier = Modifier
                .fillMaxSize()
                .windowInsetsPadding(WindowInsets.safeDrawing),
            topBar = {
                CenterAlignedTopAppBar(
                    title = { Text("游戏详情") },
                    navigationIcon = {
                        IconButton(onClick = { navController.popBackStack() }) {
                            Icon(Icons.AutoMirrored.Filled.ArrowBack, contentDescription = "返回")
                        }
                    },
                    actions = {
                        IconButton(onClick = { viewModel.showFxDialog() }) {
                            Icon(Icons.Default.Delete, contentDescription = "删除游戏")
                        }
                    },
                    colors = TopAppBarDefaults.centerAlignedTopAppBarColors(
                        containerColor = Color.Transparent
                    )
                )
            },
            floatingActionButton = {
                ExtendedFloatingActionButton(
                    onClick = {
                        if (isThisGameRunning) {
                            GameStartUtil.killGameProcess(context)
                        } else {
                            GameStartUtil.startGame(localActivity, gameInfo!!) {
                                viewModel.showRunGameTipDialog()
                            }
                        }
                    },
                    containerColor = if (isThisGameRunning) MaterialTheme.colorScheme.errorContainer else MaterialTheme.colorScheme.primary,
                    contentColor = if (isThisGameRunning) MaterialTheme.colorScheme.onErrorContainer else MaterialTheme.colorScheme.onPrimary,
                    icon = {
                        Icon(
                            if (isThisGameRunning) Icons.Default.Stop else Icons.Default.PlayArrow,
                            contentDescription = null
                        )
                    },
                    text = { Text(if (isThisGameRunning) "停止运行" else "启动游戏") }
                )
            },
            floatingActionButtonPosition = FabPosition.Center
        ) { innerPadding ->
            LazyColumn(
                modifier = Modifier
                    .fillMaxSize()
                    .padding(innerPadding),
                contentPadding = PaddingValues(bottom = 80.dp)
            ) {
                // 1. 顶部沉浸式图片展示区
                item {
                    HeroImageSection(
                        gameIcon = gameInfo?.iconPath.orEmpty(),
                        gameName = gameName,
                        onEditClick = { viewModel.inputGameName() }
                    )
                }

                // 2. 信息列表区
                item { Spacer(modifier = Modifier.height(16.dp)) }

                item {
                    InfoRow(
                        icon = Icons.Default.Book,
                        title = "游戏描述",
                        content = "游戏详情内容待完善，添加游戏介绍、版本信息、开发团队、游戏特色等。",
                    )
                }
                item {
                    InfoRow(
                        icon = Icons.Default.CalendarToday,
                        title = "创建时间",
                        content = TimeUtil.timestampToTime(gameInfo?.createTime),
                    )
                }
                item {
                    InfoRow(
                        icon = Icons.Default.History,
                        title = "最后启动时间",
                        content = TimeUtil.timestampToTime(gameInfo?.lastPlayed),
                    )
                }
                item {
                    InfoRow(
                        icon = Icons.Default.Extension,
                        title = "模组",
                        content = "点击查看",
                        onClick = {
                            gameInfo?.let {
                                if (it.modPath.isNullOrEmpty()) {
                                    val modsFolder = FileSelectorUtil.createGameModsFolder(
                                        context = context,
                                        name = gameInfo?.name.orEmpty()
                                    )
                                    it.modPath = modsFolder
                                }
                                viewModel.update(it)
                            }
                            navController.navigate(Screen.MOD.name)
                        }
                    )
                }
                item {
                    InfoRow(
                        icon = Icons.Default.ShoppingBasket,
                        title = "模组商店",
                        content = "点击查看",
                        onClick = {
                            navController.navigate(Screen.MOD_ONLINE.name)
                        }
                    )
                }
                item {
                    InfoRow(
                        icon = if (isEnableMod) Icons.Default.ToggleOn else Icons.Default.ToggleOff,
                        title = "禁用模组",
                        content = if (isEnableMod) "已启用" else "未启用",
                        onClick = {
                            gameInfo?.let {
                                isEnableMod = !isEnableMod
                                gameInfo?.let {
                                    it.isEnableMod = !isEnableMod
                                    viewModel.update(it)
                                }
                                Log.e("HJR", "isEnableMod: $isEnableMod")
                            }
                        }
                    ) {
                        gameInfo?.let { game ->
                            Switch(
                                checked = isEnableMod,
                                onCheckedChange = { isChecked ->
                                    isEnableMod = !isEnableMod
                                    gameInfo?.let {
                                        it.isEnableMod = !isEnableMod
                                        viewModel.update(it)
                                    }
                                    Log.e("HJR", "isEnableMod: $isEnableMod")
                                },
                                modifier = Modifier.scale(0.8f)
                            )
                        }
                    }
                }
//                item {
//                    InfoRow(
//                        icon = Icons.Default.Save,
//                        title = "存档管理",
//                        content = "点击查看",
//                        onClick = {
//                            if (gameInfo!!.savePath.isNullOrEmpty()) {
//                                scope.launch {
//                                    withContext(Dispatchers.IO) {
//                                        val savePath = FileSelectorUtil.createSavePath(context, gameInfo!!.name)
//                                        gameInfo!!.savePath = savePath.absolutePath
//                                        viewModel.suspendUpdate(gameInfo!!)
//                                    }
//                                    navController.navigate(Screen.SAVE_MANAGER.name)
//                                }
//                            } else {
//                                navController.navigate(Screen.SAVE_MANAGER.name)
//                            }
//                        }
//                    )
//                }
                item {
                    InfoRow(
                        icon = Icons.Default.BugReport,
                        title = "lovely日志查看",
                        content = "点击查看",
                        onClick = { navController.navigate(Screen.LOG.name) }
                    )
                }
//                item {
//                    InfoRow(
//                        icon = Icons.Default.Share,
//                        title = "分享当前模组包",
//                        content = "点击创建",
//                        onClick = { navController.navigate(Screen.CREATE_MOD_PACKAGE.name) }
//                    )
//                }
            }
        }

        // --- 弹窗逻辑：完全保留您原有的弹窗调用逻辑 ---
        if (isShowGameNameInput) {
            GameNameInputDialog(
                gameName = gameName,
                onDismiss = {
                    viewModel.dismissGameNameInput()
                },
                onConfirm = { name ->
                    gameInfo?.let {
                        viewModel.update(it.copy(name = name))
                    }
                    viewModel.dismissGameNameInput()
                },
                onNameChanged = { gameName = it },
                isShowDismissBtn = true
            )
        }

        if (isShowRunGameTipDialog) {
            gameInfo?.let {
                GameRunningTipDialog(it, onDismiss = {
                    viewModel.dismissRunGameTipDialog()
                })
            }
        }

        if (isShowFxDialog) {
            gameInfo?.let { game ->
                ConfirmDialog(
                    title = "确认删除",
                    message = "确认删除 “${game.name}” 吗？",
                    onConfirm = {
                        viewModel.dismissFxDialog()
                        viewModel.delete(game)
                        navController.popBackStack()
                    }, onDismiss = {
                        viewModel.dismissFxDialog()
                    })
            }
        }
    }
}


// region --- 美化后的辅助组件 ---

@Composable
fun HeroImageSection(gameIcon: String, gameName: String, onEditClick: () -> Unit) {
    Box(
        modifier = Modifier
            .fillMaxWidth()
            .height(250.dp)
    ) {
        GameIcon(
            base64Icon = gameIcon,
            contentDescription = gameName,
            modifier = Modifier.fillMaxSize()
        )
        Box(
            modifier = Modifier
                .fillMaxSize()
                .background(
                    Brush.verticalGradient(
                        colors = listOf(Color.Black.copy(alpha = 0.5f), Color.Transparent, Color.Black.copy(alpha = 0.8f)),
                        startY = 0f,
                        endY = 800f
                    )
                )
        )
        Row(
            modifier = Modifier
                .align(Alignment.BottomStart)
                .padding(16.dp)
                .fillMaxWidth(),
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text(
                text = gameName,
                style = MaterialTheme.typography.headlineMedium.copy(color = Color.White),
                fontWeight = FontWeight.Bold,
                modifier = Modifier.weight(1f)
            )
            IconButton(onClick = onEditClick) {
                Icon(Icons.Default.Edit, contentDescription = "编辑名称", tint = Color.White)
            }
        }
    }
}

@Composable
fun InfoRow(
    icon: ImageVector,
    title: String,
    content: String,
    onClick: (() -> Unit)? = null,
    trailingContent: @Composable (() -> Unit)? = null,
) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(16.dp))
            .let { if (onClick != null) it.clickable(onClick = onClick) else it }
            .padding(horizontal = 16.dp, vertical = 20.dp),
        verticalAlignment = Alignment.CenterVertically,
        horizontalArrangement = Arrangement.spacedBy(16.dp)
    ) {
        Icon(imageVector = icon, contentDescription = title, tint = MaterialTheme.colorScheme.primary)
        Column(modifier = Modifier.weight(1f)) {
            Text(text = title, style = MaterialTheme.typography.titleMedium)
            Spacer(modifier = Modifier.height(2.dp))
            Text(
                text = content,
                style = MaterialTheme.typography.bodyMedium,
                color = MaterialTheme.colorScheme.onSurfaceVariant,
                maxLines = 1,
                overflow = TextOverflow.Ellipsis
            )
        }
        if (trailingContent != null) {
            trailingContent()
        } else if (onClick != null) {
            Icon(
                imageVector = Icons.AutoMirrored.Filled.KeyboardArrowRight,
                contentDescription = null,
                tint = MaterialTheme.colorScheme.onSurfaceVariant.copy(alpha = 0.6f)
            )
        }
    }
}