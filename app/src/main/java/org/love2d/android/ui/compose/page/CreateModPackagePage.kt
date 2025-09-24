package org.love2d.android.ui.compose.page

import android.util.Log
import android.widget.Toast
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.ExperimentalLayoutApi
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.heightIn
import androidx.compose.foundation.layout.isImeVisible
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.safeDrawing
import androidx.compose.foundation.layout.windowInsetsPadding
import androidx.compose.foundation.layout.wrapContentSize
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.ColorScheme
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Switch
import androidx.compose.material3.Text
import androidx.compose.material3.TextField
import androidx.compose.material3.TextFieldDefaults
import androidx.compose.material3.darkColorScheme
import androidx.compose.material3.lightColorScheme
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.scale
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalFocusManager
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import com.squareup.moshi.Moshi
import org.love2d.android.CreatePackage
import org.love2d.android.ThemeConfig
import org.love2d.android.bean.CreateModDispositionBean
import org.love2d.android.room.mod.ModInfo
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.compose.TopTitleBar
import org.love2d.android.util.ModPackageCreateUtil
import java.io.File

/**
 * ClassName CreateModPackagePage
 * Description
 * Create by hjr
 * Date 2025/7/1 15:39
 */
@OptIn(ExperimentalLayoutApi::class, ExperimentalMaterial3Api::class)
@Composable
fun CreateModPackagePage(navController: NavController, viewModel: GameManagerViewModel) {
    val context = LocalContext.current

    val setting by lazy { CreateModDispositionBean() }
    setting.isCreatePackage = true

    val gameInfoState = viewModel.currentGame.collectAsState()
    val modPath = gameInfoState.value!!.modPath  // 既然保证非空，可以用!!

    val pathMods = remember(modPath) {
        viewModel.getPathMods(modPath)
    }

    val mods by pathMods.collectAsState()

    //是否启用设置配置
    var isUseSetting by remember {
        mutableStateOf(setting.isSetting)
    }

    //模组包名称
    var name by remember { mutableStateOf("") }

    val focusManager = LocalFocusManager.current
    val isKeyboardOpen = WindowInsets.isImeVisible

    LaunchedEffect(isKeyboardOpen) {
        if (!isKeyboardOpen) {
            focusManager.clearFocus()
        }
    }

    Surface(
        modifier = Modifier.fillMaxSize(),
        color = MaterialTheme.colorScheme.background,
    ) {
        Box(
            modifier = Modifier
                .fillMaxSize()
                .windowInsetsPadding(WindowInsets.safeDrawing)
        ) {
            Column(
                modifier = Modifier.fillMaxWidth()
            ) {
                TopTitleBar(navController = navController, title = "创建模组包")
                Spacer(modifier = Modifier.height(12.dp))
                LazyColumn(
                    modifier = Modifier.fillMaxWidth(),
                    contentPadding = PaddingValues(top = 10.dp, start = 16.dp, end = 16.dp, bottom = 45.dp),
                    verticalArrangement = Arrangement.spacedBy(12.dp)
                ) {
                    item {
                        TextField(value = name,
                            onValueChange = { name = it },
                            label = { Text("请输入模组包名称") },
                            modifier = Modifier.fillMaxWidth(),
                            colors = TextFieldDefaults.textFieldColors(
                                focusedIndicatorColor = Color.Transparent,
                                unfocusedIndicatorColor = Color.Transparent,
                                disabledIndicatorColor = Color.Transparent
                            )
                        )
                    }

                    item {
                        Box(
                            modifier = Modifier
                                .wrapContentSize()
                                .border(
                                    width = 1.dp, color = getInvertedColor {
                                        it.surfaceVariant
                                    }, // 你可以换成其他颜色
                                    shape = RoundedCornerShape(5.dp)
                                )
                        ) {
                            LazyColumn(
                                modifier = Modifier.heightIn(max = 280.dp), // 设置最大高度
                                contentPadding = PaddingValues(8.dp),
                                verticalArrangement = Arrangement.spacedBy(8.dp), // 设置条目间距
                            ) {
                                items(mods.size) { index ->
                                    ModFileCard(mod = mods[index])
                                }
                            }
                        }
                    }

                    item {
                        Box(modifier = Modifier.fillMaxWidth()) {
//                            GameDetailItemCard("保留设置项：",
//                                subTitle = "(实验性功能，谨慎使用)",
//                                content = if (isUseSetting) "保留" else "不保留",
//                                cardClick = {
//                                    setting.isSetting = !setting.isSetting
//                                    isUseSetting = setting.isSetting
//                                })
                            Switch(
                                checked = isUseSetting, onCheckedChange = {
                                    setting.isSetting = !setting.isSetting
                                    isUseSetting = setting.isSetting
                                }, modifier = Modifier
                                    .align(Alignment.BottomEnd)
                                    .padding(end = 14.dp)
                                    .scale(0.8f)
                            )
                        }
                    }
                }
            }
            // 固定底部按钮
            Button(
                onClick = {
                    if (name.isNotBlank()) {
                        setting.packageName = name

                        val build = Moshi.Builder().build()
                        val jsonAdapter = build.adapter(CreateModDispositionBean::class.java)
                        val manifest = jsonAdapter.toJson(setting)

                        val hPackageFolder = File(context.getExternalFilesDir(null), "hPackage")
                        if (!hPackageFolder.exists()) hPackageFolder.mkdirs()

                        val packageFolder = File(hPackageFolder, setting.packageName)
                        if (!packageFolder.exists()) packageFolder.mkdirs()

                        //创建配置文件
                        val manifestFile = File(packageFolder, CreatePackage.H_PACKAGE_MANIFEST_NAME)
                        manifestFile.writeText(manifest)
                        //创建mod目录
                        val mod = File(packageFolder, "mods")
                        if (!mod.exists()) mod.mkdirs()
                        //copy所有mod(文件夹)到当前文件夹下
                        ModPackageCreateUtil.copyDirectory(File(modPath), mod)

                        Log.e("HJR", "manifest: $manifest")
                    } else {
                        Toast.makeText(context, "请输入模组包名称", Toast.LENGTH_SHORT).show()
                    }
                }, modifier = Modifier
                    .align(Alignment.BottomCenter)
                    .padding(horizontal = 14.dp, vertical = 14.dp)
                    .fillMaxWidth()
            ) {
                Row {
                    Text(
                        text = "生成并分享", modifier = Modifier.align(Alignment.CenterVertically)
                    )
                }
            }
        }
    }
}

@Composable
fun ModFileCard(mod: ModInfo) {
    val context = LocalContext.current
    Card(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(
                elevation = 6.dp, shape = RoundedCornerShape(5.dp), clip = true // ✅ 让阴影跟着圆角裁剪
            )
            .clickable {

            }, shape = RoundedCornerShape(5.dp), colors = CardDefaults.cardColors(
            containerColor = MaterialTheme.colorScheme.surfaceVariant
        )
    ) {
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(8.dp), verticalAlignment = Alignment.CenterVertically
        ) {
            Text(
                text = mod.name,
                modifier = Modifier
                    .weight(1f)
                    .padding(end = 8.dp),
                maxLines = 2,
                overflow = TextOverflow.Ellipsis
            )
        }
    }
}

@Composable
fun getInvertedColor(originalSelector: (ColorScheme) -> Color): Color {
    val theme = ThemeConfig.rememberUserPreferredTheme()
    val isDark = theme.value
    return if (isDark) {
        lightColorScheme().let(originalSelector)
    } else {
        darkColorScheme().let(originalSelector)
    }
}