package org.love2d.android.ui.activity

import android.content.Context
import android.net.Uri
import android.util.Log
import android.widget.Toast
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewModelScope
import com.squareup.moshi.Moshi
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import org.love2d.android.BuiltInMod
import org.love2d.android.SettingConfig
import org.love2d.android.bean.LocalModManifestBean
import org.love2d.android.net.RetrofitClient
import org.love2d.android.net.UiState
import org.love2d.android.net.bean.ModListItemBean
import org.love2d.android.room.download.DownloadDatabase
import org.love2d.android.room.download.DownloadInfo
import org.love2d.android.room.download.DownloadRepository
import org.love2d.android.room.game.GameDatabase
import org.love2d.android.room.game.GameInfo
import org.love2d.android.room.game.GameRepository
import org.love2d.android.room.mod.ModDatabase
import org.love2d.android.room.mod.ModInfo
import org.love2d.android.room.mod.ModRepository
import org.love2d.android.util.FileSelectorUtil
import org.love2d.android.util.MMKVHelper
import java.io.File
import java.io.FileOutputStream
import java.io.InputStream
import java.io.OutputStream

/**
 * ClassName GameManagerViewModel
 * Description
 * Create by hjr
 * Date 2025/6/20 11:30
 */
class GameManagerViewModel(
    private val gameRepository: GameRepository,
    private val modRepository: ModRepository,
    private val downloadRepository: DownloadRepository,
) : ViewModel() {
    //-----------------------游戏数据库管理相关-----------------------

    val games: StateFlow<List<GameInfo>> = gameRepository.allGames
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())

    fun insert(game: GameInfo) {
        viewModelScope.launch { gameRepository.insertGame(game) }
    }

    fun update(game: GameInfo) {
        viewModelScope.launch { gameRepository.updateGame(game) }
    }

    suspend fun suspendUpdate(game: GameInfo) {
        gameRepository.updateGame(game)
    }

    fun delete(game: GameInfo) {
        viewModelScope.launch {
            val file = File(game.filePath)
            if (file.exists()) {
                FileSelectorUtil.deleteRecursively(file)
            }
            //遍历对应的modPath
            modRepository.deleteModsByInstallPath(game.modPath)
            //删除modPath文件夹
            FileSelectorUtil.deleteRecursively(File(game.modPath))
            gameRepository.deleteGame(game)
        }
    }

    suspend fun getGameById(id: String): GameInfo? {
        return gameRepository.getGameById(id)
    }

    suspend fun insertNetMod(downloadInfo: DownloadInfo, resultName: String) {
        val modInfo = ModInfo()
        modInfo.isLocal = false
        modInfo.resultName = resultName
        modInfo.installPath = downloadInfo.installPath
        modInfo.author = downloadInfo.author
        modInfo.cover = downloadInfo.cover
        modInfo.author_avatar_url = downloadInfo.author_avatar_url
        modInfo.created_at = downloadInfo.created_at
        modInfo.description = downloadInfo.description
        modInfo.downloaded_time = downloadInfo.downloaded_time
        modInfo.game_name = downloadInfo.game_name
        modInfo.github_repo_url = downloadInfo.github_repo_url
        modInfo.id = downloadInfo.id
        modInfo.name = downloadInfo.name
        modInfo.from = downloadInfo.from
        modInfo.repo_id = downloadInfo.repo_id
        modInfo.stars = downloadInfo.stars
        modInfo.updated_at = downloadInfo.updated_at
        modInfo.version = downloadInfo.version
        viewModelScope.launch { modRepository.insertMod(modInfo) }
    }

    suspend fun updateNetMod(downloadInfo: DownloadInfo) {
        val modInfo = modRepository.getModByModId(downloadInfo.id)
        modInfo?.let {
            Log.e("HJR", "Update LocalMod = $modInfo")
            modInfo.updated_at = downloadInfo.updated_at
            modInfo.version = downloadInfo.version
            viewModelScope.launch { modRepository.updateMod(modInfo) }
        }
    }

    suspend fun deleteNetMod(downloadInfo: DownloadInfo) {
        viewModelScope.launch {
            val downloadFile = File(downloadInfo.file_path)
            if (downloadFile.exists()) {
                downloadFile.delete()
            }
            downloadRepository.deleteDownload(downloadInfo)
            _downloadStates.update { it + (downloadInfo.id to DownloadState.Idle) }
        }
    }

    suspend fun existsModByModId(installPath: String, modId: String): Boolean {
        return modRepository.existsModInPath(installPath, modId)
    }

    fun deleteMod(mod: ModInfo) {
        viewModelScope.launch {
            val file = if (mod.isLocal) {
                File(mod.installPath, mod.name)
            } else {
                File(mod.installPath, mod.resultName)
            }
            Log.e(
                "HJR",
                "delete FileName = ${file.name} name = ${mod.name} resultName = ${mod.resultName} isLocal = ${mod.isLocal} "
            )
            if (file.exists()) {
                FileSelectorUtil.deleteRecursively(file)
            }
            modRepository.deleteMod(mod)
        }
    }

    fun insertDownload(downloadInfo: DownloadInfo) {
        viewModelScope.launch { downloadRepository.insertDownload(downloadInfo) }
    }

    fun updateDownload(downloadInfo: DownloadInfo) {
        viewModelScope.launch {
            val downloadByModId = downloadRepository.getDownloadByModId(downloadInfo.id)
            downloadByModId?.let {
                downloadByModId.version = downloadInfo.version
                downloadByModId.updated_at = downloadInfo.updated_at
                downloadRepository.updateDownload(downloadByModId)
            }
        }
    }

    //-----------------------模组管理-----------------------
    fun getPathMods(installPath: String): StateFlow<List<ModInfo>> = modRepository.getModsByInstallPathFlow(installPath)
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())

    fun getDownloadMods(): StateFlow<List<DownloadInfo>> = downloadRepository.getAllDownload()
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())

    fun getAllByStarsDesc(): StateFlow<List<DownloadInfo>> = downloadRepository.getAllByStarsDesc()
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())

    fun getAllByDownloadTimeDesc(): StateFlow<List<DownloadInfo>> = downloadRepository.getAllByDownloadCountDesc()
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())

    fun searchByNameDownloadInfo(keyWords: String): StateFlow<List<DownloadInfo>> = downloadRepository.searchByName(keyWords)
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5000), emptyList())

    //-----------------------界面操作-----------------------
    val isShowGameNameInput = MutableStateFlow(false)

    fun inputGameName() {
        isShowGameNameInput.value = true
    }

    var fileUrl: Uri? = null
    var modUrl: Uri? = null

    // 最终由 Compose 设置的名字
    var gameName = MutableStateFlow(GameNameData()) // 用作事件

    fun dismissGameNameInput() {
        isShowGameNameInput.value = false
    }

    fun dismissGameNameInput(isCreate: Boolean, gameName: String) {
        isShowGameNameInput.value = false
        val gameNameData = GameNameData(isCreate, gameName)
        this.gameName.value = gameNameData
        Log.e("HJR", "gameName: $gameNameData")
    }

    fun releaseGameNameField() {
        isShowGameNameInput.value = false
        fileUrl = null
        gameName.value = GameNameData()
    }

    var currentGame = MutableStateFlow<GameInfo?>(null)
    var currentLovelyFile = MutableStateFlow<File?>(null)

    val isShowRunGameTipDialog = MutableStateFlow(false)
    fun showRunGameTipDialog() {
        isShowRunGameTipDialog.value = true
    }

    fun dismissRunGameTipDialog() {
        isShowRunGameTipDialog.value = false
    }

    val isShowFxDialog = MutableStateFlow(false)
    fun showFxDialog() {
        isShowFxDialog.value = true
    }

    fun dismissFxDialog() {
        isShowFxDialog.value = false
    }

    fun getBuiltInModState(gamePath: String, context: Context): StateFlow<List<LocalModManifestBean>> {
        val moshi = Moshi.Builder().build()
        val adapter = moshi.adapter(LocalModManifestBean::class.java)

        val builtInModState = MutableStateFlow<List<LocalModManifestBean>>(emptyList())

        viewModelScope.launch(Dispatchers.IO) {
            getPathMods(gamePath).collect { installedMods ->
                val list = mutableListOf<LocalModManifestBean>()
                BuiltInMod.builtInModList.forEach { name ->
                    val json = FileSelectorUtil.readFileFromZipInAssets(context, name, "manifest.json")
                    if (json != null) {
                        val bean = adapter.fromJson(json)
                        bean?.apply {
                            fileName = name
                            val installed = installedMods.find { it.name == this.name }
                            if (installed != null) {
                                modInfo = installed
                                isInstall = true
                            }
                            list.add(this)
                        }
                    }
                }
                builtInModState.value = list
            }
        }

        return builtInModState
    }

    //-----------------------网络相关-----------------------
    // 1. 将 UiState 的泛型参数改为我们新的状态类 ModListState
    private val _modUiState = MutableStateFlow<UiState<ModListState>>(UiState.Loading)
    val modUiState: StateFlow<UiState<ModListState>> = _modUiState

    // 2. 在 ViewModel 内部维护当前页码
    private var currentPage = 1

    // 在 GameManagerViewModel 类中添加这个新方法
    private suspend fun updateDownloadStatesBasedOnLocalMods(remoteMods: List<DownloadInfo>) {
        // 获取当前游戏已安装的所有模组，以便进行比对
        // 注意：这里我们假设 `currentGame.value?.modPath` 存有当前游戏有效的模组安装路径
        // 一次性从数据库获取所有已安装模组的信息
        val localMods = downloadRepository.getAllDownloadList()
        val localModsMap = localMods.associateBy { it.id } // 转换为Map以提高查找效率

        remoteMods.forEach { remoteMod ->
            // 如果当前模组正在下载中，跳过状态更新，保持Downloading状态
            if (_downloadStates.value[remoteMod.id] is DownloadState.Downloading) {
                return@forEach
            }

            val localMod = localModsMap[remoteMod.id]

            val newState = if (localMod == null) {
                // 本地没有，就是未安装状态
                DownloadState.Idle
            } else {
                // 本地有，需要比对版本号
                // 注意：这里的版本号比较直接使用字符串对比，对于 "10.0" vs "9.0" 可能会出错。
                // 建议引入一个专门的版本号比较库（如 SemVer）来确保比较的准确性。
                if (remoteMod.version > localMod.version) {
                    DownloadState.Updatable // 远程版本 > 本地版本，可更新
                } else {
                    DownloadState.Installed // 否则，视为已安装
                }
            }
            _downloadStates.update { it + (remoteMod.id to newState) }
        }
    }

    // 3. 修改 getModList 方法，让它处理分页逻辑
    fun getModList(isRefresh: Boolean = false, sort: String = "stars") {
        // 如果正在加载更多，则不响应新的请求
        val currentState = (_modUiState.value as? UiState.Success)?.data
        if (currentState?.isLoadingMore == true) return

        // 如果是刷新操作，重置页码和状态
        if (isRefresh) {
            currentPage = 1
        }

        // 如果没有更多数据了，并且不是刷新，则直接返回
        if (currentState?.hasMore == false && !isRefresh) return

        viewModelScope.launch {
            // 根据是初次加载/刷新还是加载更多来设置 UI 状态
            val oldState = (_modUiState.value as? UiState.Success)?.data ?: ModListState()
            _modUiState.value = if (currentPage == 1) {
                UiState.Loading // 全屏加载
            } else {
                UiState.Success(oldState.copy(isLoadingMore = true)) // 底部加载
            }

            // 准备请求参数
            val params = hashMapOf(
                "page" to currentPage,
                "limit" to 20,
                "sort" to sort,
                "order" to "desc",
                "game_name" to "balatro"
            )

            try {
                // 4. 发起网络请求，注意 Retrofit 接口的返回类型是 ModListApiResponse
                val response = RetrofitClient.api.getModList(params) // 假设已修改返回类型

                if (response.code == 0) {
                    val currentMods = if (currentPage == 1) emptyList() else oldState.mods
                    val newMods = response.data ?: emptyList<DownloadInfo>()
                    val hasMore = response.page < response.totalPages

                    // 5. 成功后，更新状态：合并新旧列表，并更新 hasMore 状态
                    val downloadInfos = currentMods + newMods

                    // 【替换为新方法的调用】
                    updateDownloadStatesBasedOnLocalMods(downloadInfos)

                    _modUiState.value = UiState.Success(
                        ModListState(
                            mods = downloadInfos,
                            hasMore = hasMore,
                            isLoadingMore = false
                        )
                    )
                    currentPage++ // 页码加一，为下次加载做准备
                } else {
                    _modUiState.value = UiState.Error("加载失败: ${response.message}")
                }
            } catch (e: Exception) {
                _modUiState.value = UiState.Error("网络异常: ${e.message}")
            }
        }
    }

    // --- 新增：搜索结果的状态和逻辑 ---
    private val _searchUiState = MutableStateFlow<UiState<ModListState>>(UiState.Success(ModListState())) // 初始为空状态
    val searchUiState: StateFlow<UiState<ModListState>> = _searchUiState

    private var searchCurrentPage = 1
    private var currentQuery = "" // 保存当前搜索的关键词

    /**
     * 搜索模组
     * @param query 搜索关键词
     * @param isNewSearch 是否是一次全新的搜索 (用户点击搜索按钮)，如果是，则重置页码和列表
     */
    fun searchMods(query: String, isNewSearch: Boolean, sort: String = "stars") {
        // 如果是新的搜索，或者搜索词变了，就重置
        if (isNewSearch || query != currentQuery) {
            searchCurrentPage = 1
            currentQuery = query
        }

        // --- 这部分逻辑和 getModList 几乎完全一样 ---
        val currentState = (_searchUiState.value as? UiState.Success)?.data
        if (currentState?.isLoadingMore == true) return
        if (currentState?.hasMore == false && !isNewSearch) return
        if (query.isBlank()) { // 如果搜索词为空，清空结果并返回
            _searchUiState.value = UiState.Success(ModListState(mods = emptyList(), hasMore = false))
            return
        }

        viewModelScope.launch {
            val oldState = if (searchCurrentPage == 1) ModListState() else currentState!!
            _searchUiState.value = if (searchCurrentPage == 1) {
                UiState.Loading
            } else {
                UiState.Success(oldState.copy(isLoadingMore = true))
            }

            // 准备搜索参数
            val params = hashMapOf(
                "page" to searchCurrentPage,
                "limit" to 20,
                "sort" to sort,
                "order" to "desc",
                "name" to currentQuery
            )

            try {
                // 调用新的搜索 API
                val response = RetrofitClient.api.searchMod(params)

                if (response.code == 0) {
                    val currentMods = if (searchCurrentPage == 1) emptyList() else oldState.mods
                    val newMods = response.data
                    val hasMore = response.page < response.totalPages

                    // 5. 成功后，更新状态：合并新旧列表，并更新 hasMore 状态
                    val downloadInfos = currentMods + newMods

                    updateDownloadStatesBasedOnLocalMods(downloadInfos)

                    _searchUiState.value = UiState.Success(
                        ModListState(
                            mods = downloadInfos,
                            hasMore = hasMore,
                            isLoadingMore = false
                        )
                    )
                    searchCurrentPage++
                } else {
                    _searchUiState.value = UiState.Error("搜索失败: ${response.message}")
                }
            } catch (e: Exception) {
                _searchUiState.value = UiState.Error("网络异常: ${e.message}")
            }
        }
    }

    fun getModInfo(modListItemBean: ModListItemBean) {
        val params = hashMapOf(
            "id" to modListItemBean.id
        )
        viewModelScope.launch {
            val modInfo = RetrofitClient.api.getModInfo(params)
            Log.e("HJR", "ModInfo = $modInfo")
        }
    }

    // 1. 创建一个 StateFlow 来保存每个模组的下载状态
    //    键是模组的ID (String)，值是它的下载状态 (DownloadState)
    private val _downloadStates = MutableStateFlow<Map<String, DownloadState>>(emptyMap())
    val downloadStates: StateFlow<Map<String, DownloadState>> = _downloadStates.asStateFlow()

    // 修改函数签名以接收 Context
    // 在 GameManagerViewModel.kt 文件中

    fun downloadMod(mod: DownloadInfo, context: Context) {
        // 1. 如果当前模组已在下载中，则直接返回，防止重复操作
        if (_downloadStates.value[mod.id] is DownloadState.Downloading) {
            Toast.makeText(context, "${mod.name} 正在下载中...", Toast.LENGTH_SHORT).show()
            return
        }

        viewModelScope.launch(Dispatchers.IO) {
            var isUpdateOperation = false // 标记这是否是一次更新操作

            // 2. 检查这是否是一次“更新”
            val installPath = currentGame.value?.modPath
            if (!installPath.isNullOrBlank()) {
                // 从数据库查询本地是否已安装该模组
                val localMod = modRepository.getModInPath(installPath, mod.id)
                val downloadMod = downloadRepository.getDownloadByModId(mod.id)
                Log.e("HJR", "localMod = $localMod")
                if (downloadMod != null) {
                    isUpdateOperation = true
                    withContext(Dispatchers.Main) {
                        Toast.makeText(context, "开始更新 ${mod.name}...", Toast.LENGTH_SHORT).show()
                    }
                }
            }

            // 定义输入输出流变量，以便在 finally 中安全关闭
            var inputStream: InputStream? = null
            var outputStream: OutputStream? = null

            try {
                // 3. 立即更新UI状态为“下载中”
                _downloadStates.update { it + (mod.id to DownloadState.Downloading(0f)) }

                // 4. 执行网络请求，下载模组文件
                val response = RetrofitClient.api.downloadMod(mod.id)

                if (response.isSuccessful) {
                    val body = response.body() ?: throw Exception("网络响应体为空")
                    inputStream = body.byteStream()

                    // 定义文件保存路径 (例如：/data/data/your.package.name/files/download_mods/mod_name.zip)
                    val modsDir = File(context.filesDir, "download_mods")
                    if (!modsDir.exists()) modsDir.mkdirs()
                    val file = File(modsDir, "${mod.name}.zip")
                    outputStream = FileOutputStream(file)

                    // 循环读写，将文件保存到本地
                    val buffer = ByteArray(4 * 1024)
                    var bytesRead: Int
                    while (inputStream.read(buffer).also { bytesRead = it } != -1) {
                        outputStream.write(buffer, 0, bytesRead)
                    }
                    outputStream.flush()

                    // 5. 文件下载成功后，进行安装/更新操作
                    mod.isLocal = false
                    mod.downloadPath = modsDir.absolutePath
                    mod.file_path = file.absolutePath
                    mod.from = "模组商店"
                    if (isUpdateOperation) {
                        updateDownload(mod)
                    } else {
                        insertDownload(mod) // 将下载记录存入数据库
                    }

                    val isAutoInstall = MMKVHelper.getBoolean(SettingConfig.AUTO_INSTALL_MOD, true)
                    if (isUpdateOperation && !installPath.isNullOrBlank() || isAutoInstall && !installPath.isNullOrBlank()) {
                        // 调用我们修改过的解压方法，它会处理文件覆盖
                        val resultName = FileSelectorUtil.installZipFileToModPathNoInsert(
                            context = context,
                            modPath = installPath,
                            zipUri = file,
                            isUpdate = isUpdateOperation // 关键：传入更新标记
                        )

                        // 将新的模组信息插入数据库
                        mod.installPath = installPath
                        if (isUpdateOperation) {
                            Log.e("HJR","更新本地mod数据库")
                            updateNetMod(mod)
                        } else {
                            Log.e("HJR","插入本地mod数据库")
                            insertNetMod(mod, resultName)
                        }

                        withContext(Dispatchers.Main) {
                            val message = if (isUpdateOperation) "模组更新成功！" else "模组下载并安装成功！"
                            Toast.makeText(context, message, Toast.LENGTH_SHORT).show()
                        }
                    } else {
                        withContext(Dispatchers.Main) {
                            Toast.makeText(context, "模组下载成功", Toast.LENGTH_SHORT).show()
                        }
                    }

                    // 6. 更新最终UI状态
                    // 先短暂显示“成功”，给用户一个即时反馈
                    _downloadStates.update { it + (mod.id to DownloadState.Success) }
                    // 延迟2秒后，设置为持久的“已安装”状态
                    kotlinx.coroutines.delay(2000)
                    _downloadStates.update { it + (mod.id to DownloadState.Installed) }

                } else {
                    // 网络请求失败
                    throw Exception("网络请求失败: ${response.code()}")
                }

            } catch (e: Exception) {
                // 7. 捕获所有异常，更新UI状态为“失败”
                e.printStackTrace()
                _downloadStates.update { it + (mod.id to DownloadState.Error(e.message ?: "未知错误")) }
            } finally {
                // 8. 在 finally 块中确保关闭所有流
                inputStream?.close()
                outputStream?.close()
            }
        }
    }
}

/**
 * 这个密封类用于表示单个模组的下载与安装状态
 */
sealed class DownloadState {
    /** * 默认状态，表示模组【未被安装】。
     * UI应显示“下载”按钮。
     */
    data object Idle : DownloadState()

    /** * 正在下载中，包含进度值 (0.0 to 1.0)。
     * UI应显示进度条。
     */
    data class Downloading(val progress: Float) : DownloadState()

    /**
     * 状态：【已安装】。
     * 这是一个持久状态，表示模组已存在于本地，并且是最新版本。
     * UI应显示一个勾选标记或“已安装”文本。
     */
    data object Installed : DownloadState()

    /**
     * 状态：【可更新】。
     * 这是一个持久状态，表示模组已存在于本地，但服务器上有新版本。
     * UI应显示“更新”按钮。
     */
    data object Updatable : DownloadState()

    /**
     * 临时状态：【操作成功】。
     * 可以在下载或更新成功后短暂显示，用于给用户一个即时反馈，
     * 之后应转换为 `Installed` 状态。
     */
    data object Success : DownloadState()

    /** * 状态：【操作失败】。
     * UI应显示错误信息和“重试”按钮。
     */
    data class Error(val message: String) : DownloadState()
}

// 用于承载 ModShop 页面状态的数据类
data class ModListState(
    val mods: List<DownloadInfo> = emptyList(), // 累积的 Mod 列表
    val hasMore: Boolean = true, // 是否还有更多数据可加载
    val isLoadingMore: Boolean = false, // 是否正在加载下一页
)

data class GameNameData(
    var isCreate: Boolean = true,
    var gameName: String = "",
)

class GameViewModelFactory(context: Context) : ViewModelProvider.Factory {
    private val gameDao = GameDatabase.getInstance(context).gameDao()
    private val modDao = ModDatabase.getInstance(context).modInfoDao()
    private val downloadDao = DownloadDatabase.getInstance(context).downloadInfoDao()

    private val gameRepo = GameRepository(gameDao)
    private val modRepo = ModRepository(modDao)
    private val downloadRepo = DownloadRepository(downloadDao)


    override fun <T : ViewModel> create(modelClass: Class<T>): T {
        if (modelClass.isAssignableFrom(GameManagerViewModel::class.java)) {
            @Suppress("UNCHECKED_CAST")
            return GameManagerViewModel(gameRepo, modRepo, downloadRepo) as T
        }
        throw IllegalArgumentException("Unknown ViewModel class")
    }
}