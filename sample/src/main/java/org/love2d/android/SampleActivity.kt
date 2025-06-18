package org.love2d.android

import android.content.Context
import android.content.Intent
import android.net.Uri
import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.core.content.ContextCompat.startActivity
import androidx.core.content.FileProvider
import org.love2d.android.ui.theme.LÖVEForAndroidTheme
import java.io.File
import java.io.FileOutputStream

class SampleActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            LÖVEForAndroidTheme {
                    GameList(
                        modifier = Modifier.fillMaxSize()
                    )
            }
        }
    }
}

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun GameList(modifier: Modifier = Modifier) {

    Scaffold(
        modifier = modifier,
        topBar = {
            TopAppBar(
                title = { Text(text = "Games") }
            )
        }
    ){

        val context = LocalContext.current

        Column (
            modifier = Modifier.padding(it).padding(32.dp)
        ) {
            Button(
                onClick = {
                    context.launchLoveWithLuaFile()
                },
                modifier = Modifier.fillMaxWidth()
            ){
                Text(text = "Empty Game")
            }

            Spacer(modifier = Modifier.height(16.dp))

            Button(
                onClick = {
                    context.launchLoveDirectly("hello.love")
                },
                modifier = Modifier.fillMaxWidth()
            ){
                Text(text = "Hello")
            }
            Spacer(modifier = Modifier.height(16.dp))

            Button(
                onClick = {
                    context.launchLoveDirectly("snake.love")
                },
                modifier = Modifier.fillMaxWidth()
            ){
                Text(text = "Snake Demo Game")
            }


        }
    }


}

fun Context.launchLoveDirectly(luaFileName: String) {
    val inputStream = assets.open(luaFileName)
    val file = File(filesDir, luaFileName)

    inputStream.use { input ->
        file.outputStream().use { output ->
            input.copyTo(output)
        }
    }

    // Go directly to GameActivity
    val intent = Intent(this, GameActivity::class.java)
    intent.setData(Uri.fromFile(file))

    startActivity(intent)
}


fun Context.launchLoveWithLuaFile(luaFileName: String? = null) {
    if(luaFileName == null){
        val intent = Intent(this, GameActivity::class.java)
        startActivity(intent)
    }else {
        // Copy your Lua file from assets to internal storage
        val inputStream = assets.open(luaFileName)
        val file = File(filesDir, luaFileName)

        inputStream.use { input ->
            file.outputStream().use { output ->
                input.copyTo(output)
            }
        }

        // Create file URI
        val fileUri = FileProvider.getUriForFile(
            this,
            "${packageName}.fileprovider", // You'll need to set up FileProvider
            file
        )

        // Send intent to IntentReceiverActivity
        val intent = Intent(this, IntentReceiverActivity::class.java)
        intent.action = Intent.ACTION_SEND
        intent.putExtra(Intent.EXTRA_STREAM, fileUri)
        intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)

        startActivity(intent)
    }
}


private fun Context.openGame(path: String?=null){
    if(path == null){
        val intent = Intent(this, GameActivity::class.java)
        startActivity(intent)
    }else {


        val lojaFile = copyAssetToInternalStorage(this, path)
        println(">>>>> game path :" + lojaFile.absolutePath)
        println(">>>>> game content :" + lojaFile.readText())
        if (lojaFile.exists()) {
            val intent = Intent(this, GameActivity::class.java)
            intent.data = Uri.fromFile(lojaFile)
            println(">>>>> game url:" +  intent.data)
            intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_NEW_DOCUMENT)
            startActivity(intent)

//            val intent = Intent(this, IntentReceiverActivity::class.java).apply {
//                action = Intent.ACTION_SEND
//
//                val uri = Uri.fromFile(lojaFile)
//
//                putExtra(Intent.EXTRA_STREAM, uri)
//                type = "application/octet-stream" // Or "text/plain"
//                addFlags(Intent.FLAG_ACTIVITY_NEW_TASK)
//            }
//            this.startActivity(intent)


        } else {
            Toast.makeText(this, "UPS, file does not exist!", Toast.LENGTH_SHORT).show()
        }
    }
}

fun copyAssetToCache(context: Context, filename: String): File {
    val file = File(context.cacheDir, filename)
    file.parentFile?.mkdirs()
    context.assets.open(filename).use { input ->
        FileOutputStream(file).use { output ->
            input.copyTo(output)
        }
    }
    return file // Now you can use file.absolutePath
}

fun copyAssetToInternalStorage(context: Context, assetName: String): File {
    val inputStream = context.assets.open(assetName)
    val file = File(context.filesDir, assetName)

    inputStream.use { input ->
        file.outputStream().use { output ->
            input.copyTo(output)
        }
    }

    return file
}



@Preview(showBackground = true)
@Composable
fun GameListPreview() {
    LÖVEForAndroidTheme {
        GameList()
    }
}