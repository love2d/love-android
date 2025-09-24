package org.love2d.android.ui.compose

import androidx.compose.animation.core.animateFloatAsState
import androidx.compose.animation.core.tween
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.size
import androidx.compose.material3.IconButton
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.rotate
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.ColorFilter
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import org.love2d.android.executable.R
import org.love2d.android.ThemeConfig
import org.love2d.android.ui.resource.LocalUserPreferredTheme

/**
 * ClassName ThemeSwitchButton
 * Description
 * Create by hjr
 * Date 2025/6/20 11:39
 */
@Composable
fun ThemeSwitchButton() {

    val currentTheme = LocalUserPreferredTheme.current
    // 动画过渡旋转角度
    val rotation by animateFloatAsState(
        targetValue = if (currentTheme.value) 0f else 180f,
        animationSpec = tween(durationMillis = 300),
        label = "rotation"
    )

    val tintColor = if (currentTheme.value) Color.Black else Color.White

    IconButton(onClick = {
        currentTheme.value = !currentTheme.value
        ThemeConfig.setTheme(currentTheme.value)
    }) {
        Image(
            painter = painterResource(id = R.drawable.theme_mode),
            contentDescription = "切换主题",
            modifier = Modifier
                .size(24.dp)
                .rotate(rotation),
            colorFilter = ColorFilter.tint(tintColor)
        )
    }
}