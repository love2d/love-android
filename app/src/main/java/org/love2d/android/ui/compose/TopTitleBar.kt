package org.love2d.android.ui.compose

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material.IconButton
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material.icons.filled.Delete
import androidx.compose.material.icons.filled.KeyboardArrowLeft
import androidx.compose.material3.Icon
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController

/**
 * ClassName TopTitleBar
 * Description
 * Create by hjr
 * Date 2025/6/25 10:50
 */
@Composable
fun TopTitleBar(navController: NavController, title: String, isShowDelete: Boolean = false, gameDelete: () -> Unit = {}) {
    Row(
        modifier = Modifier.fillMaxWidth()
    ) {
        IconButton(onClick = { navController.popBackStack() }) {
            Icon(imageVector = Icons.Default.ArrowBack, contentDescription = Icons.Default.KeyboardArrowLeft.name)
        }

        Text(
            text = title,
            fontSize = 19.sp,
            style = MaterialTheme.typography.titleLarge,
            color = MaterialTheme.colorScheme.onSurface,
            modifier = Modifier.align(Alignment.CenterVertically)
        )
        if (isShowDelete) {
            Spacer(modifier = Modifier.weight(1f))
            Icon(
                imageVector = Icons.Filled.Delete,
                contentDescription = "删除",
                modifier = Modifier
                    .align(Alignment.CenterVertically)
                    .padding(end = 14.dp)
                    .clickable {
                        gameDelete()
                    }
            )
        }
    }
}