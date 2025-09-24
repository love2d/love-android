package org.love2d.android.ui.compose.page

import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.FloatingActionButton
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.MutableState
import androidx.compose.runtime.mutableStateOf
import androidx.compose.ui.Modifier
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import org.love2d.android.ui.compose.ThemeSwitchButton


@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun FirstCheckPage(
    currentTheme: MutableState<Boolean> = mutableStateOf(isSystemInDarkTheme()),
    onSuccess : () -> Unit = { },
) {
    Scaffold(
        topBar = {
            TopAppBar(
                title = { Text("初始化设置", fontWeight = FontWeight.Bold) },
                colors = TopAppBarDefaults.topAppBarColors(
                    containerColor = MaterialTheme.colorScheme.primary,
                    titleContentColor = MaterialTheme.colorScheme.onPrimary
                ),
                actions = {
                    ThemeSwitchButton()
                })
        },
//        bottomBar = {
//            Row(
//                modifier = Modifier
//                    .fillMaxWidth()
//                    .padding(bottom = 30.dp, end = 19.dp),  // 设置底部和右边边距
//                horizontalArrangement = Arrangement.End  // 内容靠右
//            ) {
//                FloatingActionButton(
//                    onClick = {
//                        onSuccess()
//                    },
//                    shape = RoundedCornerShape(15.dp),
//                    modifier = Modifier.size(width = 77.dp, height = 40.dp)
//                ) {
//                    Text("跳过", fontSize = 14.sp)
//                }
//            }
//        }
    ) { padding ->  // ⚠️ 这里必须接住 padding 参数
        Box(
            modifier = Modifier
                .padding(padding)
                .fillMaxSize()
        ) {
            PermissionPagerUI(onConfirm = {
                onSuccess()
            })
        }
    }
}

@Preview(showBackground = true)
@Composable
fun PreviewFirstCheckPage() {
    FirstCheckPage()
}