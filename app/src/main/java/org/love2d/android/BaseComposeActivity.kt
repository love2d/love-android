package org.love2d.android

import android.app.Activity
import android.content.Context
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.runtime.Composable
import org.love2d.android.ui.resource.AppTheme

/**
 * ClassName BaseComposeActivity
 * Description
 * Create by hjr
 * Date 2025/6/20 13:22
 */
open abstract class BaseComposeActivity(val isUsedMaterialTheme: Boolean = true) : ComponentActivity() {

    protected lateinit var localActivity : Activity
    protected lateinit var localContext : Context

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        localActivity = this
        localContext = this
        enableEdgeToEdge()
        initListener()
        setContent {
            if (isUsedMaterialTheme) {
                val rememberUserPreferredTheme = ThemeConfig.rememberUserPreferredTheme()
                Log.e("HJR", "Base Create Theme ${rememberUserPreferredTheme.value}")
                AppTheme(rememberUserPreferredTheme.value) {
                    ScreenContent()
                }
            } else ScreenContent()
        }
    }

    /**
     * 子类复写该方法，来实现自己的 Compose UI 内容
     */
    @Composable
    abstract fun ScreenContent()

    abstract fun initListener()
}