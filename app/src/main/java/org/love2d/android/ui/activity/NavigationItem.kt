package org.love2d.android.ui.activity

/**
 * ClassName NavigationItem
 * Description
 * Create by hjr
 * Date 2025/6/23 13:42
 */
sealed class NavigationItem(val route: String) {
    object Splash : NavigationItem(Screen.SPLASH.name)
    object Detail : NavigationItem(Screen.DETAIL.name)
    object Home : NavigationItem(Screen.HOME.name)
    object Setting : NavigationItem(Screen.SETTING.name)
    object Mod : NavigationItem(Screen.MOD.name)
    object Log : NavigationItem(Screen.LOG.name)
    object LogDetail : NavigationItem(Screen.LOG_DETAIL.name)
    object CreateModPackage : NavigationItem(Screen.CREATE_MOD_PACKAGE.name)
    object ModOnline : NavigationItem(Screen.MOD_ONLINE.name)
    object DownloadInfoList : NavigationItem(Screen.DOWNLOAD_INFO_LIST.name)
    object SaveManager : NavigationItem(Screen.SAVE_MANAGER.name)
}

enum class Screen {
    SPLASH,
    HOME,
    DETAIL,
    SETTING,
    MOD,
    LOG,
    LOG_DETAIL,
    CREATE_MOD_PACKAGE,
    MOD_ONLINE,
    DOWNLOAD_INFO_LIST,
    SAVE_MANAGER
}