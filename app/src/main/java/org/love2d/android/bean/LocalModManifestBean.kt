package org.love2d.android.bean

import com.squareup.moshi.JsonClass
import org.love2d.android.room.mod.ModInfo

@JsonClass(generateAdapter = true)
data class LocalModManifestBean(
    val dependencies: List<Any>,
    val description: String,
    val name: String,
    val version_number: String,
    val website_url: String,
    @Transient var modInfo : ModInfo? = null,
    @Transient var isInstall : Boolean = false,
    @Transient var fileName : String = ""
)