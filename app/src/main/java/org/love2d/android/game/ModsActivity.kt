package org.love2d.android.game

import android.app.Activity
import android.content.Context
import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.provider.OpenableColumns
import android.util.Log
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.LinearLayoutManager
import org.love2d.android.executable.databinding.ActivityModsLayoutBinding
import org.love2d.android.ui.ModAdapter
import org.love2d.android.util.ShaderFixer
import java.io.File
import java.io.FileInputStream
import java.io.FileOutputStream
import java.util.zip.ZipInputStream

/**
 * ClassName ModsActivity
 * Description
 * Create by hjr
 * Date 2025/6/17 15:12
 */
class ModsActivity : AppCompatActivity() {

    companion object {
        private const val REQUEST_CODE_FILE = 1002     // 文件选择

        fun start(context: Context, mods: ArrayList<String>) {
            val intent = Intent(context, ModsActivity::class.java)
            intent.putExtra("mods", mods)
            context.startActivity(intent)
        }
    }

    private  val modsDir by lazy { File(getExternalFilesDir(null), "mods") }

    private lateinit var binding: ActivityModsLayoutBinding

    private val mods by lazy { intent.getStringArrayListExtra("mods") }

    private val adapter by lazy { ModAdapter() }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityModsLayoutBinding.inflate(layoutInflater)

        setContentView(binding.root)

        binding.backIcon.setOnClickListener { finish() }

        binding.modRlv.layoutManager = LinearLayoutManager(this)
        binding.modRlv.adapter = adapter

        adapter.setList(mods)

        binding.addModBtn.setOnClickListener {
            openFilePicker(this, REQUEST_CODE_FILE)
        }

        adapter.setOnDeleteListener { fileName ->
            //在mods文件夹找到对应文件名的，不论是文件夹还是什么 删除掉
            deleteModByName(modsDir, fileName)
        }
    }

    fun deleteModByName(modsDir: File, fileName: String): Boolean {
        val target = File(modsDir, fileName)
        return if (target.exists()) {
            if (target.isDirectory) {
                deleteDirectoryRecursively(target)
            } else {
                target.delete()
            }
        } else {
            false
        }
    }

    // 递归删除整个文件夹
    fun deleteDirectoryRecursively(dir: File): Boolean {
        dir.listFiles()?.forEach { file ->
            if (file.isDirectory) {
                deleteDirectoryRecursively(file)
            } else {
                file.delete()
            }
        }
        return dir.delete()
    }


    // 跳转到文件选择器（支持多选）
    fun openFilePicker(context: Activity, requestCode: Int) {
        //可选择的文件类型
        val intent = Intent(Intent.ACTION_OPEN_DOCUMENT).apply {
            addCategory(Intent.CATEGORY_OPENABLE)
            type = "*/*"
        }
        context.startActivityForResult(intent, requestCode)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == REQUEST_CODE_FILE && resultCode == Activity.RESULT_OK) {
            val uri = data?.data
            if (uri != null) {
                if (!modsDir.exists()) modsDir.mkdirs()

                val fileName = queryDisplayName(uri) ?: "unknown_file"
                val destFile = File(modsDir, fileName)

                try {
                    // 1. 复制 zip 文件到 mods 文件夹
                    contentResolver.openInputStream(uri)?.use { input ->
                        FileOutputStream(destFile).use { output ->
                            input.copyTo(output)
                        }
                    }

                    // 2. 智能解压
                    val unzipFileSmart = unzipFileSmart(destFile, modsDir)

                    // 4. 检测刚刚解压出的模组目录是否包含 assets/shaders 里有 .fs 文件
                    val extractedModDir = File(modsDir, unzipFileSmart)
                    val shadersDir = File(extractedModDir, "assets/shaders")

                    Log.e("HJR","extractedModDir ${extractedModDir.absolutePath}")

                    Log.e("HJR","shadersDir ${shadersDir.absolutePath}")

                    if (shadersDir.exists() && shadersDir.isDirectory) {
                        val fsFiles = shadersDir.listFiles { file -> file.extension == "fs" }
                        if (!fsFiles.isNullOrEmpty()) {
                            // 弹窗询问是否适配
                            AlertDialog.Builder(this)
                                .setTitle("检测到着色器文件")
                                .setMessage("模组包含移动端可能不兼容的着色器文件，移动端可能无法正常渲染导致崩溃等问题？")
                                .setPositiveButton("了解") { dialog, _ ->
                                    dialog.dismiss()
                                }
                                .setNegativeButton("删除") { dialog, _ ->
                                    deleteModByName(modsDir, unzipFileSmart)
                                    dialog.dismiss()
                                }
                                .show()
                        }
                    }

                    // 3. 删除原始 zip 文件（可选）
                    destFile.delete()

                    Toast.makeText(this, "已添加: ${fileName.substringBeforeLast(".")}", Toast.LENGTH_SHORT).show()
                } catch (e: Exception) {
                    Toast.makeText(this, "复制或解压失败: ${e.message}", Toast.LENGTH_LONG).show()
                    e.printStackTrace()
                }
            }
        }
    }

    fun unzipFileSmart(zipFile: File, modsDir: File): String {
        val topLevelEntries = mutableSetOf<String>()
        var hasSubFiles = false
        var resultName : String = ""

        // 第一次遍历，收集所有顶层条目名，判断是否有子文件
        ZipInputStream(FileInputStream(zipFile)).use { zipIn ->
            var entry = zipIn.nextEntry
            while (entry != null) {
                val parts = entry.name.split("/")
                if (parts.isNotEmpty()) {
                    val firstLevel = parts[0]
                    topLevelEntries.add(firstLevel)
                    if (parts.size > 1) {
                        hasSubFiles = true
                    }
                }
                zipIn.closeEntry()
                entry = zipIn.nextEntry
            }
        }

        val targetDir = if (topLevelEntries.size == 1 && hasSubFiles) {
            // 只有一个顶层文件夹，直接解压到 modsDir/顶层文件夹名
            resultName = topLevelEntries.first()
            modsDir
        } else {
            // 多个顶层条目，创建以 zip 文件名为文件夹
            val apply = File(modsDir, zipFile.nameWithoutExtension)
            resultName = apply.name
            apply.mkdirs()
            apply
        }

        // 解压
        ZipInputStream(FileInputStream(zipFile)).use { zipIn ->
            var entry = zipIn.nextEntry
            while (entry != null) {
                val outFile = File(targetDir, entry.name)
                if (entry.isDirectory) {
                    outFile.mkdirs()
                } else {
                    outFile.parentFile?.mkdirs()
                    FileOutputStream(outFile).use { output ->
                        zipIn.copyTo(output)
                    }
                }
                zipIn.closeEntry()
                entry = zipIn.nextEntry
            }
        }

        return resultName
    }

    private fun queryDisplayName(uri: Uri): String? {
        val cursor = contentResolver.query(uri, null, null, null, null)
        cursor?.use {
            if (it.moveToFirst()) {
                val index = it.getColumnIndex(OpenableColumns.DISPLAY_NAME)
                if (index != -1) {
                    return it.getString(index)
                }
            }
        }
        return null
    }
}