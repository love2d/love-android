package org.love2d.android.ui.compose

import android.util.Log
import android.widget.Toast
import androidx.compose.foundation.Image
import androidx.compose.foundation.clickable
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.graphics.ColorFilter
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.airbnb.lottie.LottieComposition
import com.airbnb.lottie.LottieCompositionFactory
import com.airbnb.lottie.compose.LottieAnimation
import com.airbnb.lottie.compose.LottieCompositionSpec
import com.airbnb.lottie.compose.LottieConstants
import com.airbnb.lottie.compose.animateLottieCompositionAsState
import com.airbnb.lottie.compose.rememberLottieComposition
import org.love2d.android.executable.R
import org.love2d.android.ThemeConfig
import org.love2d.android.ui.resource.LocalUserPreferredTheme

@Composable
fun LottieLoading(modifier: Modifier = Modifier) {
    val composition by rememberLottieComposition(
        LottieCompositionSpec.RawRes(if (isSystemInDarkTheme()) R.raw.light_empty_animator else R.raw.night_empty_animator)
    )

    val progress by animateLottieCompositionAsState(
        composition = composition,
        iterations = LottieConstants.IterateForever // 无限循环
    )

    LottieAnimation(
        composition = composition,
        progress = { progress },
        modifier = modifier
    )
}

@Composable
fun EmptyLottie(
    emptyText: String,
    isShowAdd: Boolean = true,
    addGame: () -> Unit = {},
) {
    val context = LocalContext.current
    val current = LocalUserPreferredTheme.current
    val resId = if (current.value) R.raw.night_empty_animator else R.raw.light_empty_animator

    // 👇 用 DisposableEffect + LottieCompositionFactory 强制重载动画
    var composition by remember { mutableStateOf<LottieComposition?>(null) }

    LaunchedEffect(resId) {
        composition = LottieCompositionFactory.fromRawResSync(context, resId).value
    }

    val progress by animateLottieCompositionAsState(
        composition = composition,
        iterations = LottieConstants.IterateForever
    )

    Column(
        modifier = Modifier.fillMaxWidth(),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        composition?.let {
            LottieAnimation(
                composition = it,
                progress = { progress },
                modifier = Modifier.height(200.dp)
            )
        }

        Row(modifier = Modifier.height(40.dp)) {
            Text(
                text = emptyText,
                modifier = Modifier.align(Alignment.CenterVertically),
                fontSize = 24.sp,
            )
            if (isShowAdd) {
                Spacer(modifier = Modifier.padding(4.dp))
                Image(
                    painter = painterResource(id = R.drawable.add_circle_outline_24),
                    contentDescription = "添加",
                    modifier = Modifier
                        .align(Alignment.CenterVertically)
                        .clip(RoundedCornerShape(4.dp))
                        .clickable { addGame() },
                    colorFilter = ColorFilter.tint(MaterialTheme.colorScheme.onSurface)
                )
            }
        }
    }
}