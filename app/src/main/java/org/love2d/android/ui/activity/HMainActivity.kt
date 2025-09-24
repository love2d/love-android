package org.love2d.android.ui.activity

import android.app.Activity
import android.content.Intent
import android.util.Log
import android.widget.Toast
import androidx.activity.viewModels
import androidx.compose.animation.ExperimentalAnimationApi
import androidx.compose.animation.core.tween
import androidx.compose.animation.fadeIn
import androidx.compose.animation.fadeOut
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.SideEffect
import androidx.compose.runtime.mutableStateOf
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.lifecycle.lifecycleScope
import androidx.navigation.NavHostController
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import com.google.accompanist.systemuicontroller.rememberSystemUiController
import com.jeremyliao.liveeventbus.LiveEventBus
import kotlinx.coroutines.launch
import org.love2d.android.AppConfig
import org.love2d.android.BaseComposeActivity
import org.love2d.android.ui.compose.page.CreateModPackagePage
import org.love2d.android.ui.compose.page.DownloadInfoModPage
import org.love2d.android.ui.compose.page.EnhancedLogDetailPage
import org.love2d.android.ui.compose.page.EnhancedLovelyLogPage
import org.love2d.android.ui.compose.page.FinalFixedHeaderPage
import org.love2d.android.ui.compose.page.GameDetailPage
import org.love2d.android.ui.compose.page.HomePage
import org.love2d.android.ui.compose.page.ModPage
import org.love2d.android.ui.compose.page.SaveListPage
import org.love2d.android.ui.compose.page.SplashPage
import org.love2d.android.ui.resource.AppRoot
import org.love2d.android.ui.resource.LocalUserPreferredTheme
import org.love2d.android.util.DIR
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.GameStartUtil
import org.love2d.android.util.MMKVHelper
import kotlin.system.exitProcess

/**
 * ClassName HMainActivity
 * Description
 * Create by hjr
 * Date 2025/6/23 13:40
 */
class HMainActivity : BaseComposeActivity(false) {
    val viewModel: GameManagerViewModel by viewModels {
        GameViewModelFactory(this) // 或 this (Activity)
    }

    @Composable
    override fun ScreenContent() {
        HAppNavHost(
            navController = rememberNavController(), localActivity = localActivity, viewModel = viewModel
        )
    }

    override fun initListener() {
        val isPiracy: MutableState<Boolean> =
            mutableStateOf(MMKVHelper.getBoolean(AppConfig.IS_PIRACY_PACKAGE, false))
        if (isPiracy.value) {
            exitProcess(0)
        }

        LiveEventBus.get("KILL_GAME_PROCESS", String::class.java).observe(this@HMainActivity) {
            Log.e("HMainActivity", "KILL_GAME_PROCESS")
            GameStartUtil.killGameProcess(localActivity)
        }
        lifecycleScope.launch {
            viewModel.gameName.collect { name ->
                if (name.isCreate) {
                    if (name.gameName.isNotBlank()) {
                        FileSelectorUtil.copyLoveFileToAppDir(
                            localContext, viewModel.fileUrl!!, DIR.GAME_FOLDER_PATH, name.gameName
                        )
                    }
                } else {
                    if (name.gameName.isNotBlank()) {
                        FileSelectorUtil.renameFile(
                            localContext,
                            viewModel.currentGame.value,
                            name.gameName,
                        )
                    }
                }
                viewModel.releaseGameNameField()
            }
        }

        LiveEventBus.get("GAME_ACTIVITY_DESTROY", Boolean::class.java).observe(this@HMainActivity) {
            //kill :game_progress
            GameStartUtil.kill(this@HMainActivity)
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (resultCode == RESULT_OK) {
            when (requestCode) {
                FileSelectorUtil.REQUEST_GAME_CODE_FILE -> {
                    val handleFileResult = FileSelectorUtil.handleLoveFileResult(localActivity, data) {
                        viewModel.fileUrl = it
                        viewModel.inputGameName()
                    }
                    if (handleFileResult) {
                        Toast.makeText(localActivity, "游戏安装成功", Toast.LENGTH_SHORT).show()
                    } else {
                        Toast.makeText(localActivity, "游戏安装失败", Toast.LENGTH_SHORT).show()
                    }
                }

                FileSelectorUtil.REQUEST_MOD_CODE_FILE -> {
                    val modPath = viewModel.currentGame.value?.modPath
                    FileSelectorUtil.handleZIPFileResult(localActivity, data) { modUri ->
                        FileSelectorUtil.installZipFileToModPath(localContext, modPath = modPath.orEmpty(), zipUri = modUri)
                    }
                }

                else -> {}
            }

        }

    }
}

@OptIn(ExperimentalAnimationApi::class)
@Composable
fun HAppNavHost(
    navController: NavHostController,
    startDestination: String = NavigationItem.Splash.route,
    localActivity: Activity,
    viewModel: GameManagerViewModel,
) {
    val context = LocalContext.current

    val systemUiController = rememberSystemUiController()
    val currentTheme = LocalUserPreferredTheme.current

    AppRoot() {
        NavHost(navController = navController, startDestination = startDestination) {
            composable(Screen.SPLASH.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                SplashPage(navController = navController)
            }

            composable(Screen.HOME.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                HomePage(
                    navController = navController, localActivity = localActivity, viewModel = viewModel, currentTheme
                )
                SideEffect {
                    systemUiController.setStatusBarColor(
                        color = Color.Transparent, // 或 MaterialTheme.colorScheme.background 等
                        darkIcons = currentTheme.value
                    )
                }
            }

            composable(Screen.DETAIL.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                GameDetailPage(
                    viewModel = viewModel,
                    navController = navController,
                    localActivity = localActivity
                )
                SideEffect {
                    systemUiController.setStatusBarColor(
                        color = Color.Transparent, // 或 MaterialTheme.colorScheme.background 等
                        darkIcons = !currentTheme.value
                    )
                }
            }

            composable(Screen.MOD.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                ModPage(navController = navController, localActivity, viewModel = viewModel)
            }

            composable(Screen.LOG.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                EnhancedLovelyLogPage(navController = navController, viewModel = viewModel)
            }

            composable(Screen.LOG_DETAIL.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                EnhancedLogDetailPage(navController = navController, viewModel = viewModel)
            }

            composable(Screen.CREATE_MOD_PACKAGE.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                CreateModPackagePage(navController = navController, viewModel = viewModel)
            }

            composable(Screen.MOD_ONLINE.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                FinalFixedHeaderPage(navController = navController, viewModel = viewModel)
            }

            composable(Screen.DOWNLOAD_INFO_LIST.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                DownloadInfoModPage(navController = navController, viewModel = viewModel)
            }

            composable(Screen.SAVE_MANAGER.name, enterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, exitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }, popEnterTransition = {
                fadeIn(animationSpec = tween(durationMillis = 300))
            }, popExitTransition = {
                fadeOut(animationSpec = tween(durationMillis = 300))
            }) {
                SaveListPage(navController = navController, viewModel = viewModel)
            }
        }
    }
}
