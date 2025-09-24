package org.love2d.android.util

import android.util.Log
import java.io.File

object ShaderFixer {
    fun fixShaders(shadersDir: File) {
        if (!shadersDir.exists() || !shadersDir.isDirectory) {
            showLog("路径不存在或不是目录: ${shadersDir.absolutePath}")
            return
        }

        val shaderFiles = shadersDir.walkTopDown().filter {
            it.isFile && (it.extension == "fs" || it.extension == "vs")
        }.toList()

        if (shaderFiles.isEmpty()) {
            showLog("没有找到 .fs/.vs 文件")
            return
        }

        for (file in shaderFiles) {
            try {
                val originalContent = file.readText(Charsets.UTF_8)
                val originalLines = originalContent.lines()

                if (originalLines.size >= 25) {
                    showLog("文件: ${file.name} 修复前第25行: ${originalLines[24]}")
                }

                val fixedContent = fixShaderContent(originalContent)
                val fixedLines = fixedContent.lines()

                if (fixedLines.size >= 25) {
                    showLog("文件: ${file.name} 修复后第25行: ${fixedLines[24]}")
                }

                if (fixedContent != originalContent) {
                    // 备份原文件
                    val backupFile = File(file.absolutePath + ".bak")
                    if (!backupFile.exists()) {
                        file.copyTo(backupFile)
                    }

                    file.writeText(fixedContent, Charsets.UTF_8)
                    showLog("✅ 修复完成: ${file.absolutePath}")

                    // 打印变动行
                    originalLines.zip(fixedLines).forEachIndexed { i, (a, b) ->
                        if (a != b) {
                            showLog("第${i + 1}行变动:\n  原: $a\n  新: $b")
                        }
                    }
                } else {
                    showLog("✅ 文件无需修复: ${file.absolutePath}")
                }

            } catch (e: Exception) {
                showLog("❌ 修复失败: ${file.absolutePath}, 异常: ${e.message}")
            }
        }
    }

    fun fixShaderContent(content: String): String {
        var result = content

        // 1. 替换所有函数中 int 参数为 float（如 sqrt(4) -> sqrt(4.0)）
        //    支持常见函数：sqrt, sin, cos, tan, pow, exp, log, mod, clamp, mix, etc.
        val funcs = listOf("sqrt", "sin", "cos", "tan", "exp", "log", "abs", "inversesqrt")
        funcs.forEach { func ->
            val regex = Regex("""\b$func\(\s*(\d+)(?![\d.])\s*\)""")
            result = regex.replace(result) {
                val number = it.groupValues[1]
                "$func(${number}.0)"
            }
        }

        // 2. 替换除法：/ 后接整数的写法（如 /2 -> /2.0）
        val regexDivisionInt = Regex("""/(?=\s*\d+(?!\.))(\s*)(\d+)(?![\d.])""")
        result = regexDivisionInt.replace(result) {
            val spaces = it.groupValues[1]
            val number = it.groupValues[2]
            "/$spaces${number}.0"
        }

        // 3. 替换加法（+）减法（-）乘法（*）中出现的整数为浮点
        val regexArithFloat = Regex("""([+\-*])\s*(\d+)(?![\d.])""")
        result = regexArithFloat.replace(result) {
            val op = it.groupValues[1]
            val number = it.groupValues[2]
            "$op ${number}.0"
        }

        return result
    }

    private fun showLog(message: String) {
        Log.e("HJR-ShaderFix", message)
    }
}
