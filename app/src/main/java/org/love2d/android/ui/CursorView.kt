package org.love2d.android.ui

import android.content.Context
import android.graphics.*
import android.util.AttributeSet
import android.view.View
import androidx.annotation.DrawableRes
import androidx.core.content.ContextCompat

class CursorView @JvmOverloads constructor(
    context: Context,
    attrs: AttributeSet? = null
) : View(context, attrs) {

    enum class StyleType {
        DEFAULT, TEXT, IMAGE
    }

    // --- 属性区 ---
    private var styleType: StyleType = StyleType.DEFAULT
    private var customText: String = "指针"
    private var textPaint: Paint = Paint(Paint.ANTI_ALIAS_FLAG).apply {
        color = Color.WHITE
        textSize = 32f * resources.displayMetrics.density
        textAlign = Paint.Align.CENTER
    }

    private var customImage: Bitmap? = null
    private var customImageSize = 48f * resources.displayMetrics.density

    private val cursorPath = Path()
    private val tailPath = Path() // <-- 尾巴路径

    private val cursorPaintFill = Paint(Paint.ANTI_ALIAS_FLAG).apply {
        style = Paint.Style.FILL
        color = 0xFF000000.toInt()
    }
    private val cursorPaintStroke = Paint(Paint.ANTI_ALIAS_FLAG).apply {
        style = Paint.Style.STROKE
        color = 0xFFFFFFFF.toInt()
        strokeWidth = resources.displayMetrics.density * 1.5f
        strokeJoin = Paint.Join.ROUND
        setShadowLayer(
            resources.displayMetrics.density * 2f,
            resources.displayMetrics.density * 0.5f,
            resources.displayMetrics.density * 0.5f,
            0x55000000
        )
    }

    private var cursorX = -1f
    private var cursorY = -1f

    // 可自定义的属性
    private var rotationAngle = -15f
    private var sizeScale = 0.8f      // ⬅️ 稍微矮一些
    private var widthScale = 1.2f     // ⬅️ 稍微宽一些，防止“太瘦”

    init {
        setBackgroundColor(Color.TRANSPARENT)
        buildDefaultCursorPath()
    }

    // --- 构建路径 ---
    private fun buildDefaultCursorPath() {
        val density = resources.displayMetrics.density

        val h = 20f * density * sizeScale     // 主体高度（缩短一点）
        val w = 8f * density * widthScale    // 主体宽度（变宽一点）
        val tailHeight = 10f * density * sizeScale
        val tailWidth = 2f * density * widthScale

        // 主体箭头路径（对称三角形）
        cursorPath.reset()
        cursorPath.apply {
            moveTo(0f, 0f)
            lineTo(-w / 2f, h)
            lineTo(0f, h * 0.85f)
            lineTo(w / 2f, h)
            close()
        }

//        // 尾巴路径：窄短矩形
//        tailPath.reset()
//        tailPath.apply {
//            moveTo(-tailWidth / 2f, h)
//            lineTo(-tailWidth / 2f, h + tailHeight)
//            lineTo(tailWidth / 2f, h + tailHeight)
//            lineTo(tailWidth / 2f, h)
//            close()
//        }
    }

    // --- 绘制逻辑 ---
    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        if (cursorX < 0 || cursorY < 0) return

        canvas.save()
        canvas.translate(cursorX, cursorY)
        canvas.rotate(rotationAngle)

        when (styleType) {
            StyleType.DEFAULT -> {
//                canvas.drawPath(tailPath, cursorPaintStroke)
//                canvas.drawPath(tailPath, cursorPaintFill)

                // 先描边再填充，确保边框在上层
                canvas.drawPath(cursorPath, cursorPaintStroke)
                canvas.drawPath(cursorPath, cursorPaintFill)
            }

            StyleType.TEXT -> {
                canvas.drawText(customText, 0f, 0f, textPaint)
            }

            StyleType.IMAGE -> {
                customImage?.let {
                    val half = customImageSize / 2
                    canvas.drawBitmap(it, -half, -half, null)
                }
            }
        }

        canvas.restore()
    }

    // --- 更新位置 ---
    fun updateCursorPosition(x: Float, y: Float) {
        cursorX = x
        cursorY = y
        invalidate()
    }

    // --- 自定义接口区 ---
    fun setCursorStyle(style: StyleType) {
        styleType = style
        invalidate()
    }

    fun setCursorText(text: String) {
        customText = text
        invalidate()
    }

    fun setCursorImage(bitmap: Bitmap, sizeDp: Float = 48f) {
        customImage = bitmap
        customImageSize = sizeDp * resources.displayMetrics.density
        invalidate()
    }

    fun setFillColor(color: Int, alpha: Int = 255) {
        cursorPaintFill.color = (color and 0x00FFFFFF) or (alpha shl 24)
        invalidate()
    }

    fun setStrokeColor(color: Int, alpha: Int = 255) {
        cursorPaintStroke.color = (color and 0x00FFFFFF) or (alpha shl 24)
        invalidate()
    }

    fun setRotationAngle(degrees: Float) {
        rotationAngle = degrees
        invalidate()
    }

    fun setSizeScale(scale: Float) {
        sizeScale = scale.coerceIn(0.3f, 3f)
        buildDefaultCursorPath()
        invalidate()
    }

    fun setWidthScale(scale: Float) {
        widthScale = scale.coerceIn(0.3f, 3f)
        buildDefaultCursorPath()
        invalidate()
    }
}
