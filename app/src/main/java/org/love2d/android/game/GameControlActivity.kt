package org.love2d.android.game

import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import org.love2d.android.GameActivity
import org.love2d.android.executable.databinding.ActivityGameControlLayoutBinding
import java.io.File

/**
 * ClassName GameControlActivity
 * Description
 * Create by hjr
 * Date 2025/6/16 18:20
 */
class GameControlActivity : AppCompatActivity() {

    private lateinit var binding: ActivityGameControlLayoutBinding

    private val library = arrayOf("lovely", "dobby")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityGameControlLayoutBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // 获取外部文件目录的 mods 子目录
        val modsDir = getExternalFilesDir(null)?.resolve("mods")
        if (modsDir != null && !modsDir.exists()) {
            modsDir.mkdirs()
        }

        binding.openModes.setOnClickListener {
            openModsFolder(modsDir)
        }

        binding.joinGame.setOnClickListener {
            loadLibrary()
            startGameActivity()
        }
    }

    private fun loadLibrary() {
        library.forEach { libName ->
            System.loadLibrary(libName) // 加载 lib.so
        }
    }

    private fun openModsFolder(modsDir: File?) {
        if (modsDir == null || !modsDir.exists()) {
            Toast.makeText(this, "mods 文件夹不存在", Toast.LENGTH_SHORT).show()
            return
        }

        //获取所有mods文件夹下的内容存储为ArrayList<String>
        val modsList = modsDir.list()?.toList()?.toCollection(ArrayList()) ?: emptyList<String?>().toCollection(ArrayList())

        ModsActivity.start(this, modsList)
    }

    private fun startGameActivity() {
        val mainIntent = intent
        val intent = Intent(this, GameActivity::class.java)

        if (mainIntent.action == Intent.ACTION_SEND) {
            // Convert to simpler intent that our GameActivity can process.
            val uri = mainIntent.getParcelableExtra<Uri>(Intent.EXTRA_STREAM)
            intent.setData(uri)
            intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
        }

        startActivity(intent)
    }
}