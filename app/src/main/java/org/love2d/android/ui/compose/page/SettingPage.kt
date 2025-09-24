package org.love2d.android.ui.compose.page

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
import androidx.compose.material.icons.outlined.InstallMobile
import androidx.compose.material.icons.outlined.Mouse
import androidx.compose.material.icons.outlined.ScreenLockLandscape
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Switch
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import org.love2d.android.SettingConfig
import org.love2d.android.util.MMKVHelper

/**
 * 定义设置项右侧的控件类型
 */
enum class SettingControlType {
    ARROW,  // 导航箭头
    SWITCH, // 切换开关
    NONE    // 无控件
}

/**
 * ClassName SettingPage
 * Description 应用设置页面
 * Create by Gemini
 * Date 2025/08/08
 */
@Composable
fun SettingPage() {
    // 用于控制开关状态的示例
    var enableTouch2Mouse by remember { mutableStateOf(MMKVHelper.getBoolean(SettingConfig.TOUCH_TO_MOUSE, false)) }

    // 用于控制屏幕锁定(左)开关状态的示例
    var enableScreenLockLeft by remember { mutableStateOf(MMKVHelper.getBoolean(SettingConfig.SCREEN_LOCK_LEFT, false)) }
    // 用于控制屏幕锁定(右)开关状态的示例
    var enableScreenLockRight by remember { mutableStateOf(MMKVHelper.getBoolean(SettingConfig.SCREEN_LOCK_RIGHT, false)) }

    // 模组自动安装
    var enableModAutoInstall by remember { mutableStateOf(MMKVHelper.getBoolean(SettingConfig.AUTO_INSTALL_MOD, true)) }


    // 使用 LazyColumn 实现可滚动的页面
    LazyColumn(
        modifier = Modifier
            .fillMaxSize()
            .background(MaterialTheme.colorScheme.surface),
        contentPadding = PaddingValues(vertical = 16.dp),
    ) {
        // --- 通用设置 ---
        item {
            Column(
                modifier = Modifier.padding(horizontal = 16.dp),
                verticalArrangement = Arrangement.spacedBy(8.dp)
            ) {
                SectionHeader("通用")
                
                SettingCard(
                    icon = Icons.Outlined.ScreenLockLandscape,
                    title = "横屏锁定（左）",
                    content = "打开后强制锁定为横屏",
                    controlType = SettingControlType.SWITCH,
                    switchState = enableScreenLockLeft,
                    onSwitchChange = { newState ->
                        // 更新当前开关的状态
                        enableScreenLockLeft = newState
                        MMKVHelper.putBoolean(SettingConfig.SCREEN_LOCK_LEFT, newState)

                        // 如果此开关被打开，则必须关闭另一个开关，以实现互斥
                        if (newState) {
                            enableScreenLockRight = false
                            MMKVHelper.putBoolean(SettingConfig.SCREEN_LOCK_RIGHT, false)
                        }
                    }
                )

                SettingCard(
                    icon = Icons.Outlined.ScreenLockLandscape,
                    title = "横屏锁定（右）",
                    content = "打开后强制锁定为横屏",
                    controlType = SettingControlType.SWITCH,
                    switchState = enableScreenLockRight,
                    onSwitchChange = { newState ->
                        // 更新当前开关的状态
                        enableScreenLockRight = newState
                        MMKVHelper.putBoolean(SettingConfig.SCREEN_LOCK_RIGHT, newState)

                        // 如果此开关被打开，则必须关闭另一个开关，以实现互斥
                        if (newState) {
                            enableScreenLockLeft = false
                            MMKVHelper.putBoolean(SettingConfig.SCREEN_LOCK_LEFT, false)
                        }
                    }
                )

                SettingCard(
                    icon = Icons.Outlined.InstallMobile,
                    title = "模组下载后自动安装",
                    content = "打开后会自动安装模组商店下载的模组（默认开启）",
                    controlType = SettingControlType.SWITCH,
                    switchState = enableModAutoInstall,
                    onSwitchChange = { newState ->
                        enableModAutoInstall = newState
                        MMKVHelper.putBoolean(SettingConfig.AUTO_INSTALL_MOD, enableModAutoInstall)
                    }
                )
            }
        }

        item {
            Spacer(modifier = Modifier.height(16.dp))
        }

        // --- 通知设置 ---
        item {
            Column(
                modifier = Modifier.padding(horizontal = 16.dp),
                verticalArrangement = Arrangement.spacedBy(8.dp)
            ) {
                SectionHeader("实验性功能")
                // 消息通知：带有 Switch 控件
                SettingCard(
                    icon = Icons.Outlined.Mouse,
                    title = "模拟鼠标事件",
                    content = "打开后会将触屏模拟为鼠标",
                    controlType = SettingControlType.SWITCH,
                    switchState = enableTouch2Mouse,
                    onSwitchChange = {
                        enableTouch2Mouse = it
                        MMKVHelper.putBoolean(SettingConfig.TOUCH_TO_MOUSE, enableTouch2Mouse)
                    }
                )
            }
        }
    }
}

/**
 * 设置项卡片，明确支持箭头和Switch控件
 * @param icon 左侧图标
 * @param title 标题
 * @param content 描述内容
 * @param controlType 右侧控件的类型 (ARROW, SWITCH, NONE)
 * @param switchState Switch的状态，仅当 controlType 为 SWITCH 时有效
 * @param onSwitchChange Switch状态改变的回调，仅当 controlType 为 SWITCH 时有效
 * @param onClick 整个卡片的点击事件
 */
@Composable
fun SettingCard(
    icon: ImageVector,
    title: String,
    content: String,
    modifier: Modifier = Modifier,
    controlType: SettingControlType = SettingControlType.ARROW,
    switchState: Boolean = false,
    onSwitchChange: (Boolean) -> Unit = {},
    onClick: (() -> Unit)? = null,
) {
    val finalOnClick = when (controlType) {
        // 如果是Switch类型，点击整行也应该能改变开关状态
        SettingControlType.SWITCH -> {
            { onSwitchChange(!switchState) }
        }
        // 否则使用传入的onClick
        else -> onClick
    }

    Row(
        modifier = modifier
            .fillMaxWidth()
            .clip(RoundedCornerShape(16.dp))
            .background(MaterialTheme.colorScheme.surfaceContainer)
            .let {
                // 仅当 finalOnClick 不为 null 时才应用 clickable 修饰符
                if (finalOnClick != null) it.clickable(onClick = finalOnClick) else it
            }
            .padding(horizontal = 16.dp, vertical = 20.dp),
        verticalAlignment = Alignment.CenterVertically,
        horizontalArrangement = Arrangement.spacedBy(16.dp)
    ) {
        Icon(
            imageVector = icon,
            contentDescription = title,
            modifier = Modifier.size(24.dp),
            tint = MaterialTheme.colorScheme.primary
        )
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

        // 根据 controlType 决定右侧显示什么控件
        when (controlType) {
            SettingControlType.ARROW -> {
                Icon(
                    imageVector = Icons.AutoMirrored.Filled.KeyboardArrowRight,
                    contentDescription = null,
                    tint = MaterialTheme.colorScheme.onSurfaceVariant.copy(alpha = 0.6f)
                )
            }

            SettingControlType.SWITCH -> {
                // Switch 的 onCheckedChange 直接使用传入的 lambda，
                // 这样可以防止点击 Switch 本身时触发两次状态变更
                Switch(
                    checked = switchState,
                    onCheckedChange = onSwitchChange
                )
            }

            SettingControlType.NONE -> {
                // 不显示任何控件
            }
        }
    }
}

@Preview(showBackground = true)
@Composable
fun SettingPagePreview() {
    // 建议在您的 AppTheme 中预览以获得正确的颜色
    // YourAppTheme {
    SettingPage()
    // }
}