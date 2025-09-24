package org.love2d.android.ui.compose.page

import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.size
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import kotlinx.coroutines.delay
import org.love2d.android.AppConfig

import org.love2d.android.ThemeConfig
import org.love2d.android.executable.R
import org.love2d.android.ui.activity.NavigationItem
import org.love2d.android.ui.compose.UserNoticeDialog
import org.love2d.android.ui.resource.AppTheme
import org.love2d.android.util.MMKVHelper


@Composable
fun SplashPage(navController: NavController) {
    val isFirstStart = MMKVHelper.getBoolean(AppConfig.IS_FIRST_START, true)
    val currentTheme = ThemeConfig.rememberUserPreferredTheme()
    var isShowFirstCheckPage by remember { mutableStateOf(true) }
    val isShowDialog = remember { mutableStateOf(true) }

    if (isFirstStart) {
        AppTheme(useDarkTheme = currentTheme.value) {
            UserNoticeDialog(show = isShowDialog.value) {
                isShowDialog.value = false
            }
            if (!isShowDialog.value) {
                if (isShowFirstCheckPage) {
                    FirstCheckPage(currentTheme, onSuccess = {
                        isShowFirstCheckPage = false
                    })
                }
            }
            if (!isShowFirstCheckPage) {
                SplashScreen(navController, isFirstStart)
            }
        }
    } else {
        SplashScreen(navController, isFirstStart)
    }
}

private fun goHome(navController: NavController) {
    navController.navigate(NavigationItem.Home.route) {
        popUpTo(NavigationItem.Splash.route) {
            inclusive = true // 把 Splash 一起移除
        }
        launchSingleTop = true // 避免重复跳转到 Home
    }
}

@Composable
fun SplashScreen(navController: NavController, isFirstStart: Boolean) {
    Box(
        modifier = Modifier.Companion
            .fillMaxSize(), // 可以替换为 MaterialTheme.colorScheme.background
        contentAlignment = Alignment.Companion.Center
    ) {
        Image(
            painter = painterResource(id = R.drawable.icon),
            contentDescription = "Splash Logo",
            modifier = Modifier.Companion.size(200.dp), // 可根据需求设置尺寸
            contentScale = ContentScale.Companion.Fit
        )
        LaunchedEffect(Unit) {
            delay(500)
            if (isFirstStart) MMKVHelper.putBoolean(AppConfig.IS_FIRST_START, false)
            goHome(navController)
        }
    }
}