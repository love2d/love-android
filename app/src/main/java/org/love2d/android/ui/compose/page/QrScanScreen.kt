package org.love2d.android.ui.compose.page

import android.util.Log
import androidx.annotation.OptIn
import androidx.camera.core.CameraSelector
import androidx.camera.core.ExperimentalGetImage
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageProxy
import androidx.camera.core.Preview
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.camera.view.PreviewView
import androidx.compose.runtime.Composable
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.viewinterop.AndroidView
import androidx.core.content.ContextCompat
import androidx.lifecycle.compose.LocalLifecycleOwner
import com.google.mlkit.vision.barcode.BarcodeScanner
import com.google.mlkit.vision.barcode.BarcodeScanning
import com.google.mlkit.vision.common.InputImage

/**
 * ClassName QrScanScreen
 * Description
 * Create by hjr
 * Date 2025/7/9 14:24
 */
@Composable
fun CameraQrScanner(
    modifier: Modifier = Modifier,
    shouldScan: Boolean = true, // ✅ 控制是否识别
    screenRunning : Boolean = false,
    onScanSuccess: (String) -> Unit
) {
    val context = LocalContext.current
    val lifecycleOwner = LocalLifecycleOwner.current
    val cameraProviderFuture = remember { ProcessCameraProvider.getInstance(context) }
    // ✅ 用于同步外部最新的值到 Analyzer 闭包中
    val currentShouldScan by rememberUpdatedState(shouldScan)
    val currentOnScanSuccess by rememberUpdatedState(onScanSuccess)
    val currentScreenRunning by rememberUpdatedState(screenRunning)
    Log.e("HJR","shouldScan = $shouldScan")

    AndroidView(
        modifier = modifier,
        factory = { ctx ->
            val previewView = PreviewView(ctx)

            cameraProviderFuture.addListener({
                val cameraProvider = cameraProviderFuture.get()

                val preview = Preview.Builder().build().also {
                    it.setSurfaceProvider(previewView.surfaceProvider)
                }

                val barcodeScanner = BarcodeScanning.getClient()
                val imageAnalyzer = ImageAnalysis.Builder()
                    .setBackpressureStrategy(ImageAnalysis.STRATEGY_KEEP_ONLY_LATEST)
                    .build()
                    .also { analysis ->
                        analysis.setAnalyzer(ContextCompat.getMainExecutor(ctx)) { imageProxy ->
                            if (!currentScreenRunning && currentShouldScan) { // ✅ 现在能拿到最新状态
                                processImageProxy(barcodeScanner, imageProxy, currentOnScanSuccess)
                            } else {
                                imageProxy.close()
                            }
                        }
                    }

                val cameraSelector = CameraSelector.DEFAULT_BACK_CAMERA

                try {
                    cameraProvider.unbindAll()
                    cameraProvider.bindToLifecycle(
                        lifecycleOwner, cameraSelector, preview, imageAnalyzer
                    )
                } catch (e: Exception) {
                    e.printStackTrace()
                }

            }, ContextCompat.getMainExecutor(ctx))

            previewView
        }
    )
}


@OptIn(ExperimentalGetImage::class)
fun processImageProxy(
    scanner: BarcodeScanner,
    imageProxy: ImageProxy,
    onResult: (String) -> Unit,
) {
    val mediaImage = imageProxy.image ?: run {
        imageProxy.close()
        return
    }

    val inputImage =
        InputImage.fromMediaImage(mediaImage, imageProxy.imageInfo.rotationDegrees)

    scanner.process(inputImage)
        .addOnSuccessListener { barcodes ->
            for (barcode in barcodes) {
                val rawValue = barcode.rawValue
                if (rawValue != null) {
                    onResult(rawValue)
                }
            }
        }
        .addOnFailureListener {
            // 失败可忽略
        }
        .addOnCompleteListener {
            imageProxy.close()
        }
}


