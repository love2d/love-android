package org.love2d.android.ui.compose.page

import android.app.Activity
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.safeDrawing
import androidx.compose.foundation.layout.windowInsetsPadding
import androidx.compose.foundation.pager.HorizontalPager
import androidx.compose.foundation.pager.rememberPagerState
import androidx.compose.material3.Divider
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Tab
import androidx.compose.material3.TabRow
import androidx.compose.material3.TabRowDefaults
import androidx.compose.material3.TabRowDefaults.tabIndicatorOffset
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.runtime.setValue
import androidx.compose.runtime.snapshotFlow
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.navigation.NavController
import kotlinx.coroutines.launch
import org.love2d.android.ui.activity.GameManagerViewModel
import org.love2d.android.ui.compose.TopTitleBar

@Composable
fun ModPage(
    navController: NavController,
    localActivity: Activity,
    viewModel: GameManagerViewModel
) {
    val gameInfoState = viewModel.currentGame.collectAsState()

    var selectedTab by remember { mutableIntStateOf(0) }
    val scope = rememberCoroutineScope()
    val title = listOf("已安装", "内置模组")

    val pagerState = rememberPagerState(initialPage = 0, pageCount = { title.size })

    LaunchedEffect(pagerState) {
        snapshotFlow { pagerState.currentPage }.collect { page ->
            selectedTab = page
        }
    }

    Surface(
        modifier = Modifier
            .fillMaxSize(),
        color = MaterialTheme.colorScheme.background,
    ) {
        Column(
            modifier = Modifier
                .fillMaxSize()
                .windowInsetsPadding(WindowInsets.safeDrawing)
        ) {
            TopTitleBar(navController = navController, title = "模组列表")
            TopTabComposeView(
                tabTitles = title,
                selectedIndex = selectedTab,
                onTabSelected = {
                    selectedTab = it
                    scope.launch {
                        pagerState.animateScrollToPage(it)
                    }
                },
                modifier = Modifier.fillMaxWidth(),
            )
            Box() {
                HorizontalPager(
                    userScrollEnabled = false,
                    state = pagerState,
                    modifier = Modifier.fillMaxSize()
                ) { index ->
                    Box(
                        modifier = Modifier.fillMaxSize(),
                        contentAlignment = Alignment.Center
                    ) {
                        when (index) {
                            0 -> {
                                EnhancedModListPage(
                                    localActivity,
                                    gameInfoState.value?.modPath.orEmpty(),
                                    viewModel
                                ) { mod ->
                                    viewModel.deleteMod(mod)
                                }
                            }
                            1 -> {
                                LocalModPage(gameInfoState.value!!, viewModel) {}
                            }
                        }
                    }
                }
            }
        }
    }
}

@Composable
fun TopTabComposeView(
    modifier: Modifier = Modifier,
    tabTitles: List<String> = listOf("Tab 1", "Tab 2"),
    selectedIndex: Int = 0,
    onTabSelected: (Int) -> Unit = {},
) {
    TabRow(
        selectedTabIndex = selectedIndex,
        modifier = modifier,
        indicator = { tabPositions ->
            TabRowDefaults.SecondaryIndicator(
                modifier = Modifier
                    .tabIndicatorOffset(tabPositions[selectedIndex])
                    .height(3.dp),
                color = MaterialTheme.colorScheme.primary
            )
        },
        divider = {
            Divider(thickness = 1.dp, color = MaterialTheme.colorScheme.surfaceVariant)
        },
        containerColor = MaterialTheme.colorScheme.surface
    ) {
        tabTitles.forEachIndexed { index, title ->
            Tab(
                selected = selectedIndex == index,
                onClick = { onTabSelected(index) },
                text = {
                    Text(
                        text = title,
                        color = if (selectedIndex == index)
                            MaterialTheme.colorScheme.primary
                        else
                            MaterialTheme.colorScheme.onSurfaceVariant,
                        style = MaterialTheme.typography.bodyMedium
                    )
                }
            )
        }
    }
}
