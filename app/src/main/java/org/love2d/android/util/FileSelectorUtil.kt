package org.love2d.android.util

import android.app.Activity
import android.content.Context
import android.content.Intent
import android.net.Uri
import android.os.Environment
import android.provider.OpenableColumns
import android.util.Base64
import android.util.Log
import android.widget.Toast
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import org.love2d.android.room.game.GameInfo
import org.love2d.android.room.mod.ModInfo
import org.love2d.android.ui.compose.page.getSaveFile
import org.love2d.android.util.DIR.GAME_FOLDER_PATH
import java.io.BufferedInputStream
import java.io.BufferedOutputStream
import java.io.File
import java.io.FileInputStream
import java.io.FileOutputStream
import java.io.IOException
import java.io.InputStream
import java.util.zip.ZipEntry
import java.util.zip.ZipFile
import java.util.zip.ZipInputStream
import java.util.zip.ZipOutputStream

/**
 * ClassName FileSelectorUtil
 * Description
 * Create by hjr
 * Date 2025/6/20 11:24
 */
object FileSelectorUtil {

    const val REQUEST_GAME_CODE_FILE = 1002     // 文件选择
    const val REQUEST_MOD_CODE_FILE = 10025   // 文件选择

    // 跳转到文件选择器
    fun openFilePicker(context: Activity, requestCode: Int) {
        //可选择的文件类型
        val intent = Intent(Intent.ACTION_OPEN_DOCUMENT).apply {
            addCategory(Intent.CATEGORY_OPENABLE)
            type = "*/*" // 先限制为应用类型
        }
        context.startActivityForResult(intent, requestCode)
    }

    // 处理文件选择返回结果（多选）
    fun handleLoveFileResult(context: Context, data: Intent?, loveFile: (Uri) -> Unit): Boolean {
        if (data == null) {
            Toast.makeText(context, "没有选择文件", Toast.LENGTH_SHORT).show()
        } else {
            val uri: Uri? = data.data
            val handleLoveFile = handleLoveFile(context, uri)
            if (handleLoveFile) {
                loveFile(uri!!)
            } else {
                Toast.makeText(context, "不是.love文件", Toast.LENGTH_SHORT).show()
            }
            return handleLoveFile
        }
        return false
    }

    fun handleZIPFileResult(context: Context, data: Intent?, zipFile: (Uri) -> Unit): Boolean {
        if (data == null) {
            Toast.makeText(context, "没有选择文件", Toast.LENGTH_SHORT).show()
        } else {
            val uri: Uri? = data.data
            val handleZIPFile = handleZIPFile(context, uri)
            if (handleZIPFile) {
                zipFile(uri!!)
            } else {
                Toast.makeText(context, "不是.zip文件", Toast.LENGTH_SHORT).show()
            }
        }
        return false
    }

    private fun needCreateTopLevelFolder(context: Context, zipUri: Uri): Boolean {
        val topLevelNames = mutableSetOf<String>()
        context.contentResolver.openInputStream(zipUri)?.use { inputStream ->
            ZipInputStream(inputStream).use { zipInputStream ->
                var entry: ZipEntry?
                while (zipInputStream.nextEntry.also { entry = it } != null) {
                    entry?.let { zipEntry ->
                        topLevelNames.add(zipEntry.name.substringBefore("/"))

                        if (topLevelNames.size > 1 || (topLevelNames.size == 1 && !zipEntry.name.contains(
                                "/"
                            ))
                        ) {
                            return true
                        }
                        zipInputStream.closeEntry()
                    }
                }
            }
        }
        return false
    }

    private fun needCreateTopLevelFolder(context: Context, zipUri: File): Boolean {
        val topLevelNames = mutableSetOf<String>()
        zipUri.inputStream().use { inputStream ->
            ZipInputStream(inputStream).use { zipInputStream ->
                var entry: ZipEntry?
                while (zipInputStream.nextEntry.also { entry = it } != null) {
                    entry?.let { zipEntry ->
                        topLevelNames.add(zipEntry.name.substringBefore("/"))

                        if (topLevelNames.size > 1 || (topLevelNames.size == 1 && !zipEntry.name.contains(
                                "/"
                            ))
                        ) {
                            return true
                        }
                        zipInputStream.closeEntry()
                    }
                }
            }
            return false
        }
    }

    private fun needCreateTopLevelFolder(inputStream: InputStream): Boolean {
        val entryNames = mutableListOf<String>()
        ZipInputStream(inputStream).use { zip ->
            var entry: ZipEntry?
            while (zip.nextEntry.also { entry = it } != null) {
                entry?.name?.let { entryNames.add(it) }
                zip.closeEntry()
            }
        }
        val topDirs = entryNames.mapNotNull { it.substringBefore("/") }.toSet()
        return topDirs.size > 1 || topDirs.none { it.isNotBlank() }
    }

    private fun getAllZipEntryNames(context: Context, zipUri: Uri): List<String> {
        val names = mutableListOf<String>()
        context.contentResolver.openInputStream(zipUri)?.use { inputStream ->
            ZipInputStream(inputStream).use { zipStream ->
                var entry: ZipEntry? = zipStream.nextEntry
                while (entry != null) {
                    names.add(entry.name)
                    entry = zipStream.nextEntry
                }
            }
        }
        return names
    }

    private fun getAllZipEntryNames(context: Context, zipUri: File): List<String> {
        val names = mutableListOf<String>()
        zipUri.inputStream().use { inputStream ->
            ZipInputStream(inputStream).use { zipStream ->
                var entry: ZipEntry? = zipStream.nextEntry
                while (entry != null) {
                    names.add(entry.name)
                    entry = zipStream.nextEntry
                }
            }
        }
        return names
    }

    fun installZipFileToModPath(context: Context, modPath: String, zipUri: Uri) {
        val buffer = ByteArray(1024)
        val modDir = File(modPath).apply { mkdirs() }

        val fileNameFromUri = getFileNameFromUri(context, zipUri).toString().removeSuffix(".zip")
        val folder = File(modDir, fileNameFromUri)
        var resultName = fileNameFromUri

        CoroutineScope(Dispatchers.IO).launch {
            val needTopFolder = needCreateTopLevelFolder(context, zipUri)
            Log.e("HJR", "needCreateTopLevelFolder: $needTopFolder")
            // 判断已存在情况
            if (needTopFolder && folder.exists()) {
                withContext(Dispatchers.Main) {
                    Toast.makeText(
                        context,
                        "已存在同名文件夹：${folder.name}，跳过解压",
                        Toast.LENGTH_SHORT
                    ).show()
                }
                return@launch
            } else if (!needTopFolder) {
                val entryNames = getAllZipEntryNames(context, zipUri)
                val topDirs = entryNames.mapNotNull { it.substringBefore("/") }.toSet()
                val alreadyExists = topDirs.any { File(modDir, it).exists() }
                if (alreadyExists) {
                    withContext(Dispatchers.Main) {
                        Toast.makeText(context, "解压内容已存在，跳过解压", Toast.LENGTH_SHORT).show()
                    }
                    return@launch
                }
            }

            val targetDir = if (needTopFolder) {
                folder.mkdirs()
                folder
            } else {
                modDir
            }

            context.contentResolver.openInputStream(zipUri)?.use { inputStream ->
                ZipInputStream(inputStream).use { zipInputStream ->
                    var entry: ZipEntry?
                    while (zipInputStream.nextEntry.also { entry = it } != null) {
                        entry?.let { zipEntry ->
                            val outFile = File(targetDir, zipEntry.name)
                            if (zipEntry.isDirectory) {
                                outFile.mkdirs()
                                if (!needTopFolder) {
                                    resultName = zipEntry.name.substringBefore("/")
                                }
                            } else {
                                outFile.parentFile?.mkdirs()
                                FileOutputStream(outFile).use { outputStream ->
                                    var len: Int
                                    while (zipInputStream.read(buffer).also { len = it } > 0) {
                                        outputStream.write(buffer, 0, len)
                                    }
                                }
                            }
                            zipInputStream.closeEntry()
                        }
                    }
                }
            }

            // 插入数据库
            val modInfo = ModInfo().apply {
                isLocal = true
                name = resultName
                from = "$fileNameFromUri.zip"
                installPath = modPath
            }
            ModDbUtil.insertMod(modInfo)
        }
    }

    // 【修改点 1】: 在方法签名中增加 isUpdate 参数
    suspend fun installZipFileToModPathNoInsert(
        context: Context,
        modPath: String,
        zipUri: File,
        isUpdate: Boolean = false // 新增参数
    ): String {
        val buffer = ByteArray(1024)
        val modDir = File(modPath).apply { mkdirs() }

        val fileNameFromUri = zipUri.name.removeSuffix(".zip")
        val folder = File(modDir, fileNameFromUri)
        var resultName = fileNameFromUri

        val needTopFolder = needCreateTopLevelFolder(context, zipUri)
        Log.e("HJR", "needCreateTopLevelFolder: $needTopFolder")

        // 【修改点 2】: 在执行解压前，根据 isUpdate 参数决定是否删除旧文件夹
        if (isUpdate) {
            val targetFolder = if (needTopFolder) folder else File(modDir, resultName)
            if (targetFolder.exists()) {
                Log.d("HJR", "更新操作：删除旧文件夹 ${targetFolder.absolutePath}")
                deleteRecursively(targetFolder)
            }
        }

        // 【修改点 3】: 仅在非更新操作时才检查文件是否存在
        if (!isUpdate) {
            if (needTopFolder && folder.exists()) {
                withContext(Dispatchers.Main) {
                    Toast.makeText(
                        context,
                        "已存在同名文件夹：${folder.name}，跳过解压",
                        Toast.LENGTH_SHORT
                    ).show()
                }
                return resultName
            } else if (!needTopFolder) {
                val entryNames = getAllZipEntryNames(context, zipUri)
                val topDirs = entryNames.mapNotNull { it.substringBefore("/") }.toSet()
                val alreadyExists = topDirs.any { File(modDir, it).exists() }
                if (alreadyExists) {
                    withContext(Dispatchers.Main) {
                        Toast.makeText(context, "解压内容已存在，跳过解压", Toast.LENGTH_SHORT).show()
                    }
                    // 注意：如果zip包内有多个文件夹，这里可能需要返回顶层文件夹的名字
                    return topDirs.firstOrNull() ?: resultName
                }
            }
        }

        val targetDir = if (needTopFolder) {
            folder.mkdirs()
            folder
        } else {
            modDir
        }

        // ...后续的解压逻辑保持不变...
        withContext(Dispatchers.IO) {
            zipUri.inputStream().use { inputStream ->
                ZipInputStream(inputStream).use { zipInputStream ->
                    var entry: ZipEntry?
                    while (zipInputStream.nextEntry.also { entry = it } != null) {
                        entry?.let { zipEntry ->
                            val outFile = File(targetDir, zipEntry.name)
                            if (zipEntry.isDirectory) {
                                outFile.mkdirs()
                                if (!needTopFolder) {
                                    // 在非 TopFolder 模式下，resultName 应该是解压出的根目录名
                                    val dirName = zipEntry.name.substringBefore('/')
                                    if (dirName.isNotEmpty()) resultName = dirName
                                }
                            } else {
                                outFile.parentFile?.mkdirs()
                                FileOutputStream(outFile).use { outputStream ->
                                    var len: Int
                                    while (zipInputStream.read(buffer).also { len = it } > 0) {
                                        outputStream.write(buffer, 0, len)
                                    }
                                }
                            }
                            zipInputStream.closeEntry()
                        }
                    }
                }
            }
        }

        return resultName
    }


    fun installZipFromAssetsToModPath(context: Context, modPath: String, assetZipName: String) {
        val buffer = ByteArray(1024)
        val modDir = File(modPath).apply { mkdirs() }

        val fileNameFromAsset = assetZipName.removeSuffix(".zip")
        val folder = File(modDir, fileNameFromAsset)
        var resultName = fileNameFromAsset

        CoroutineScope(Dispatchers.IO).launch {
            val needTopFolder = needCreateTopLevelFolder(context.assets.open(assetZipName))
            Log.e("HJR", "needCreateTopLevelFolder (assets): $needTopFolder")

            // 冲突检测
            if (needTopFolder && folder.exists()) {
                withContext(Dispatchers.Main) {
                    Toast.makeText(
                        context,
                        "已存在同名文件夹：${folder.name}，跳过解压",
                        Toast.LENGTH_SHORT
                    ).show()
                }
                return@launch
            }

            val targetDir = if (needTopFolder) {
                folder.mkdirs()
                folder
            } else {
                modDir
            }

            context.assets.open(assetZipName).use { inputStream ->
                ZipInputStream(inputStream).use { zipInputStream ->
                    var entry: ZipEntry?
                    while (zipInputStream.nextEntry.also { entry = it } != null) {
                        entry?.let { zipEntry ->
                            val outFile = File(targetDir, zipEntry.name)
                            if (zipEntry.isDirectory) {
                                outFile.mkdirs()
                                if (!needTopFolder) {
                                    resultName = zipEntry.name.substringBefore("/")
                                }
                            } else {
                                outFile.parentFile?.mkdirs()
                                FileOutputStream(outFile).use { outputStream ->
                                    var len: Int
                                    while (zipInputStream.read(buffer).also { len = it } > 0) {
                                        outputStream.write(buffer, 0, len)
                                    }
                                }
                            }
                            zipInputStream.closeEntry()
                        }
                    }
                }
            }

            // 插入数据库
            val modInfo = ModInfo().apply {
                isLocal = true
                name = resultName
                from = assetZipName
                installPath = modPath
            }
            ModDbUtil.insertMod(modInfo)
        }
    }


    private fun handleLoveFile(context: Context, path: Uri?): Boolean {
        // 处理选择的文件
        if (path == null || path.path.isNullOrEmpty()) return false
        val nameFromUri = getFileNameFromUri(context, path)
        Log.e("HJR", "nameFromUri: $nameFromUri")
        return nameFromUri?.endsWith(".love", ignoreCase = true) == true
    }

    private fun handleZIPFile(context: Context, path: Uri?): Boolean {
        // 处理选择的文件
        if (path == null || path.path.isNullOrEmpty()) return false
        val nameFromUri = getFileNameFromUri(context, path)
        Log.e("HJR", "nameFromUri: $nameFromUri")
        return nameFromUri?.endsWith(".zip", ignoreCase = true) == true
    }

    fun getFileNameFromUri(context: Context, uri: Uri): String? {
        val cursor = context.contentResolver.query(uri, null, null, null, null)
        return cursor?.use {
            val nameIndex = it.getColumnIndex(OpenableColumns.DISPLAY_NAME)
            if (it.moveToFirst() && nameIndex != -1) {
                it.getString(nameIndex)
            } else null
        }
    }

    fun copyLoveFileToAppDir(
        context: Context,
        sourceUri: Uri,
        destDir: File,
        fileName: String
    ): Boolean {
        val destFile = File(destDir, "${fileName}.love")
        try {
            context.contentResolver.openInputStream(sourceUri)?.use { inputStream ->
                destFile.outputStream().use { outputStream ->
                    inputStream.copyTo(outputStream)
                }
            }
            CoroutineScope(Dispatchers.IO).launch {
                val name = fileName.replace(".love", "")
                //在APP目录下创建对应的mod目录
                val modsPath = createGameModsFolder(context, name)
                val savePath = createSavePath(context, name)
                GameDbUtil.insertGame(
                    GameInfo(
                        name = name,
                        createTime = System.currentTimeMillis(),
                        filePath = destFile.absolutePath,
                        savePath = savePath.absolutePath,
                        modPath = modsPath,
                        iconPath = null,
                        lastPlayed = 0
                    )
                )
            }
            return true
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return false
    }

    fun createGameModsFolder(context: Context, name: String): String {
        val modsDir = File(context.getExternalFilesDir(null), "${name}_mods")
        if (!modsDir.exists()) {
            modsDir.mkdirs()
        }
        return modsDir.absolutePath
    }

    private fun renameGameModsFolder(
        context: Context,
        oldName: String,
        newName: String
    ): String {
        val modsRoot = context.getExternalFilesDir(null) ?: return ""

        val oldModsDir = File(modsRoot, "${oldName}_mods")
        val newModsDir = File(modsRoot, "${newName}_mods")

        return if (oldModsDir.exists() && oldModsDir.isDirectory) {
            if (newModsDir.exists()) {
                Log.w("ModsRename", "目标文件夹已存在，未重命名：${newModsDir.name}")
                newModsDir.absolutePath // 直接返回已存在的新目录（或可改成 null）
            } else {
                val success = oldModsDir.renameTo(newModsDir)
                if (success) newModsDir.absolutePath else ""
            }
        } else {
            Log.w("ModsRename", "旧文件夹不存在：${oldModsDir.name}")
            ""
        }
    }

    private fun renameSaveFolder(
        context: Context,
        oldName: String,
        newName: String,
    ) {
        val saveRoot = File(context.getExternalFilesDir(null), "save/love/$oldName-LOVE")
        val newSaveDir = File(context.getExternalFilesDir(null), "save/love/$newName-LOVE")

        if (saveRoot.exists() && saveRoot.isDirectory) {
            if (newSaveDir.exists()) {
                Log.w("SaveRename", "目标文件夹已存在，未重命名：${newSaveDir.name}")
            } else {
                val success = saveRoot.renameTo(newSaveDir)
                if (success) {
                    Log.i("SaveRename", "保存文件夹重命名成功：${oldName} -> ${newName}")
                } else {
                    Log.w("SaveRename", "保存文件夹重命名失败：${oldName} -> ${newName}")
                }
            }
        } else {
            Log.w("SaveRename", "旧文件夹不存在：${saveRoot.name}")
        }
    }

    //修改指定路径的文件名
    fun renameFile(context: Context, oldGame: GameInfo?, newName: String): Boolean {
        if (oldGame == null) return false
        val oldFile = File(GAME_FOLDER_PATH, "${oldGame.name}.love")
        val newFile = File(GAME_FOLDER_PATH, "$newName.love")
        if (oldFile.exists() && oldFile.isFile) {
            if (newFile.exists()) {
                Toast.makeText(context, "文件已存在", Toast.LENGTH_SHORT).show()
                return false
            } else {
                val renameGameModsFolder = renameGameModsFolder(context, oldGame.name, newName)
                renameSaveFolder(context, oldGame.name, newName)
                oldFile.renameTo(newFile)
                oldGame.name = newName
                oldGame.modPath = renameGameModsFolder
                oldGame.filePath = newFile.absolutePath
                CoroutineScope(Dispatchers.IO).launch {
                    GameDbUtil.updateGame(oldGame)
                }
                return true
            }
        } else {
            Toast.makeText(context, "文件不存在", Toast.LENGTH_SHORT).show()
            return false
        }
    }

    private fun readFileFromLove(loveFile: File, innerFilePath: String): String? {
        ZipFile(loveFile).use { zip ->
            val entry = zip.getEntry(innerFilePath)
            if (entry != null) {
                zip.getInputStream(entry).use { input ->
                    return input.bufferedReader().readText()
                }
            }
        }
        return null // 文件不存在
    }

    //检测传入的Name是否存在GAME_FOLDER_PATH下的
    fun checkGameFileExists(name: String): Boolean {
        val gameFile = File(GAME_FOLDER_PATH, "$name.love")
        return gameFile.exists()
    }

    //检测本地是否已经存在了GAME_FOLDER_NAME
    fun checkOrCreateLocalGameFolder(): Boolean {
        val externalStorageDirectory = Environment.getExternalStorageDirectory()
        val gameFolder = File(externalStorageDirectory, DIR.GAME_FOLDER_NAME)

        Log.e("HJR", "gameFolder: $gameFolder")
        return if (gameFolder.exists()) {
            Log.e("HJR", "gameFolder 存在")
            true
        } else {
            val mkdirs = gameFolder.mkdirs()
            Log.e("HJR", "gameFolder 创建: $mkdirs")
            mkdirs
            // 尝试创建目录，成功返回 true，失败返回 false
        }
    }

    // 检测本地是否已经存在了MODS_FOLDER_NAME
    fun checkOrCreateLocalModsFolder(context: Context): Boolean {
        val modsFolder = File(context.getExternalFilesDir(null), DIR.MODS_FOLDER_NAME)

        Log.e("HJR", "modsFolder: $modsFolder")
        return if (modsFolder.exists()) {
            Log.e("HJR", "modsFolder 存在")
            true
        } else {
            val mkdirs = modsFolder.mkdirs()
            Log.e("HJR", "modsFolder 创建: $mkdirs")
            mkdirs
            // 尝试创建目录，成功返回 true，失败返回 false
        }
    }

    //检测GAME_FOLDER_PATH下的.love文件是否在数据库存在 不存在则添加
    internal fun checkGameFileExists(context: Context) {
        CoroutineScope(Dispatchers.IO).launch {
            if (!GAME_FOLDER_PATH.exists() || !GAME_FOLDER_PATH.isDirectory) return@launch
            val dao = GameDbUtil.getGameDao()
            val existingGames = dao.getAllGamesNow().map { it.filePath }

            GAME_FOLDER_PATH.listFiles { file ->
                file.extension == "love"
            }?.forEach { file ->
                if (file.absolutePath !in existingGames) {
                    //创建modPath
                    val modsFolder = createGameModsFolder(context, file.nameWithoutExtension)
                    val savePath = createSavePath(context, file.nameWithoutExtension)
                    val gameInfo = GameInfo(
                        name = file.nameWithoutExtension,
                        filePath = file.absolutePath,
                        iconPath = null,
                        savePath = savePath.absolutePath,
                        modPath = modsFolder,
                        lastPlayed = System.currentTimeMillis()
                    )
                    dao.insertGame(gameInfo)
                }
            }

            //反向校验 如果文件夹没有该文件 但是数据库有 则删除
            val existingFiles = GAME_FOLDER_PATH.listFiles { file ->
                file.extension == "love"
            }?.map { it.absolutePath }
            val existingIds = dao.getAllGamesNow().map { it.filePath }
            existingIds.forEach { id ->
                if (existingFiles?.contains(id) != true) {
                    dao.deleteGame(dao.getGameById(id)!!)
                }
            }
        }
    }

    suspend fun createSavePath(context: Context, gameName: String): File {
        val file = getSaveFile(context, gameName)
        if (!file.exists()) {
            file.mkdirs()
        }
        return file
    }

    fun deleteRecursively(file: File): Boolean {
        if (file.isDirectory) {
            val children = file.listFiles()
            if (children != null) {
                for (child in children) {
                    deleteRecursively(child)
                }
            }
        }
        return file.delete()
    }

    fun readFileFromZipInAssets(context: Context, zipAssetName: String, targetFileName: String): String? {
        context.assets.open(zipAssetName).use { inputStream ->
            ZipInputStream(BufferedInputStream(inputStream)).use { zipInputStream ->
                var entry: ZipEntry?
                while (zipInputStream.nextEntry.also { entry = it } != null) {
                    if (entry?.name == targetFileName) {
                        return zipInputStream.bufferedReader().use { it.readText() }
                    }
                    zipInputStream.closeEntry()
                }
            }
        }
        return null // 找不到目标文件
    }

    fun getLovelyLogList(context: Context, modPath: String): Array<out File>? {
        val modDir = File(modPath,"lovely/log")
        return modDir.listFiles()?.reversedArray()
    }


    fun zipDirectory(sourceDir: File, outputZip: File) {
        ZipOutputStream(BufferedOutputStream(FileOutputStream(outputZip))).use { zos ->
            zipDirRecursive(sourceDir, sourceDir.name, zos)
        }
    }

    private fun zipDirRecursive(fileToZip: File, parentPath: String, zos: ZipOutputStream) {
        if (fileToZip.isHidden) return

        if (fileToZip.isDirectory) {
            val files = fileToZip.listFiles()
            if (files.isNullOrEmpty()) {
                // 添加空目录
                val entry = ZipEntry("$parentPath/")
                zos.putNextEntry(entry)
                zos.closeEntry()
                return
            }

            for (childFile in files) {
                zipDirRecursive(childFile, "$parentPath/${childFile.name}", zos)
            }
        } else {
            FileInputStream(fileToZip).use { fis ->
                val zipEntry = ZipEntry(parentPath)
                zos.putNextEntry(zipEntry)

                val buffer = ByteArray(1024)
                var length: Int
                while (fis.read(buffer).also { length = it } > 0) {
                    zos.write(buffer, 0, length)
                }
                zos.closeEntry()
            }
        }
    }

    fun base64ToZip(context: Context, base64: String) {
        try {
            val outputZip = File(context.cacheDir, "wifiSave-LOVE.zip")
            if (outputZip.exists()) {
                outputZip.delete()
                outputZip.createNewFile()
            } else outputZip.createNewFile()
            val bytes = Base64.decode(base64, Base64.DEFAULT)
            outputZip.outputStream().use { it.write(bytes) }
            Log.e("HJR", "✅ Zip 文件已写入：${outputZip.absolutePath}")
            unzip(context,outputZip)
        } catch (e: Exception) {
            e.printStackTrace()
            Log.e("HJR", "❌ 解码失败：${e.message}")
        }
    }

    /**
     * 将 ZIP 文件解压缩到指定的目录。
     *
     * @param zipFile 要解压缩的 ZIP 文件。
     * @param outputDir 解压缩后文件存放的目标目录。
     * @throws IOException 如果发生 I/O 错误。
     * @throws SecurityException 如果检测到不安全的路径（路径遍历攻击）。
     */
    fun unzip(context: Context,zipFile: File) {
        val outputDir = File(context.getExternalFilesDir(null),"save/love/wifi-save-LOVE")

        // 确保目标目录存在，如果不存在则创建
        if (!outputDir.exists()) {
            outputDir.mkdirs()
        } else {
            deleteRecursively(outputDir)
            outputDir.mkdirs()
        }

        // 标准化目标目录的路径，用于安全检查
        val outputDirPath = outputDir.canonicalPath

        // 使用 ZipInputStream 来读取 ZIP 文件内容
        ZipInputStream(zipFile.inputStream().buffered()).use { zis ->
            // 遍历 ZIP 文件中的每一个条目（文件或目录）
            var zipEntry = zis.nextEntry
            while (zipEntry != null) {
                val newFile = File(outputDir, zipEntry.name)

                // --- 安全性检查 ---
                // 确保解压后的文件路径仍然在目标目录之内
                val newFilePath = newFile.canonicalPath
                if (!newFilePath.startsWith(outputDirPath)) {
                    throw SecurityException("检测到不安全的条目: ${zipEntry.name} (路径遍历攻击)")
                }

                if (zipEntry.isDirectory) {
                    // 如果是目录，则创建它
                    if (!newFile.isDirectory && !newFile.mkdirs()) {
                        throw IOException("无法创建目录: $newFile")
                    }
                } else {
                    // 如果是文件，先确保其父目录存在
                    val parent = newFile.parentFile
                    if (parent != null && !parent.isDirectory && !parent.mkdirs()) {
                        throw IOException("无法创建父目录: $parent")
                    }

                    // 将条目内容写入新文件
                    FileOutputStream(newFile).use { fos ->
                        zis.copyTo(fos)
                    }
                }

                // 读取下一个条目
                zis.closeEntry()
                zipEntry = zis.nextEntry
            }
        }
    }
}

object DIR {
    const val MODS_FOLDER_NAME = "mods"
    const val GAME_FOLDER_NAME = "hLauncherGame"

    val GAME_FOLDER_PATH =
        File(Environment.getExternalStorageDirectory().toString() + "/" + GAME_FOLDER_NAME)
}