package org.love2d.android.ui.compose.page

import android.app.Activity
import android.util.Log
import androidx.compose.animation.ExperimentalSharedTransitionApi
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.NavigationBar
import androidx.compose.material3.NavigationBarItem
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.text.font.FontWeight
import androidx.navigation.NavController
import org.love2d.android.executable.R
import org.love2d.android.room.game.GameInfo
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.activity.Screen
import org.love2d.android.ui.compose.GameNameInputDialog
import org.love2d.android.ui.compose.GameRunningTipDialog
import org.love2d.android.ui.compose.ThemeSwitchButton
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.GameStartUtil

/**
 * ClassName HomePage
 * Description
 * Create by hjr
 * Date 2025/6/23 13:53
 */
@OptIn(ExperimentalSharedTransitionApi::class)
@Composable
fun HomePage(
    navController: NavController,
    localActivity: Activity,
    viewModel: GameManagerViewModel,
    currentTheme: MutableState<Boolean>,
) {
    GameListPage(viewModel, currentTheme, localActivity, navController)
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun GameListPage(
    viewModel: GameManagerViewModel,
    currentTheme: MutableState<Boolean>,
    localActivity: Activity,
    navController: NavController
) {
    //获取的游戏列表
    val games by viewModel.games.collectAsState(initial = emptyList())
    Log.e("HJR", "games: $games")

    // 底部导航栏数据
    val navItems = listOf(
        BottomBarItem(R.drawable.casino_24_tab, "游戏"),
        BottomBarItem(R.drawable.baseline_info_24, "关于"),
        BottomBarItem(R.drawable.settings_24_tab, "设置"),
    )

    // 底部导航栏选中项
    var selectedIndex by remember { mutableIntStateOf(0) }

    //是否展示输入游戏名称弹窗
    val isShowGameNameInput = viewModel.isShowGameNameInput.collectAsState()
    var gameName by remember { mutableStateOf("") }

    //游戏运行弹窗
    val isShowRunGameTipDialog = viewModel.isShowRunGameTipDialog.collectAsState()

    //要运行的游戏
    var readyRunGame by remember {
        mutableStateOf<GameInfo?>(null)
    }

    //当前运行游戏检测
    var thisGame by remember {
        mutableStateOf(false)
    }
    val isRunningGameInfo = GameStartUtil.currentRunningGame.collectAsState()
    if (isRunningGameInfo.value?.second?.id == readyRunGame?.id) {
        thisGame = true
    } else if (isRunningGameInfo.value == null) {
        thisGame = false
    }


    Scaffold(topBar = {
        TopAppBar(
            title = { Text(navItems[selectedIndex].label, fontWeight = FontWeight.Bold) },
            colors = TopAppBarDefaults.topAppBarColors(
                containerColor = MaterialTheme.colorScheme.primary,
                titleContentColor = MaterialTheme.colorScheme.onPrimary
            ),
            actions = {
                ThemeSwitchButton()
            })
    }, bottomBar = {
        NavigationBar {
            navItems.forEachIndexed { index, item ->
                NavigationBarItem(
                    selected = selectedIndex == index,
                    onClick = { selectedIndex = index },
                    icon = {
                        Icon(
                            painter = painterResource(id = item.icon),
                            contentDescription = item.label
                        )
                    },
                    alwaysShowLabel = false,
                    label = { Text(item.label) })
            }
        }
    }) { innerPadding ->
        // 中间内容区域
        Box(
            modifier = Modifier
                .padding(innerPadding)
                .fillMaxSize(), contentAlignment = Alignment.Center
        ) {
            when (selectedIndex) {
                0 -> {
                    EnhancedGamePage_SingleColumn(
                        games,
                        modifier = Modifier
                            .fillMaxSize(),
                        addGame = {
                            FileSelectorUtil.openFilePicker(
                                localActivity,
                                FileSelectorUtil.REQUEST_GAME_CODE_FILE,
                            )
                        }, onGameCardClick = {
                            viewModel.currentGame.value = it
                            navController.navigate(Screen.DETAIL.name)
                        }, viewModel = viewModel,
                        onGameStart = {
                            if (isRunningGameInfo.value == null) {
                                GameStartUtil.startGame(localActivity, it)
                            } else if (thisGame && isRunningGameInfo.value?.second?.id == it.id) {
                                GameStartUtil.killGameProcess(localActivity)
                            } else {
                                readyRunGame = it
                                viewModel.showRunGameTipDialog()
                            }
                        }
                    )
                }
                1 -> {
                    AboutScreen_Scrollable()
                }

                else -> {
                    SettingPage()
                }
            }

            if (isShowGameNameInput.value) {
                GameNameInputDialog(
                    gameName = gameName,
                    onDismiss = {
                        viewModel.dismissGameNameInput()
                    },
                    onConfirm = { name ->
                        gameName = name
                        viewModel.dismissGameNameInput(true, gameName)
                        gameName = ""
                    },
                    onNameChanged = { gameName = it }
                )
            }

            if (isShowRunGameTipDialog.value) {
                GameRunningTipDialog(readyRunGame!!, onDismiss = {
                    readyRunGame = null
                    viewModel.dismissRunGameTipDialog()
                })
            }
        }
    }
}

data class BottomBarItem(val icon: Int, val label: String)