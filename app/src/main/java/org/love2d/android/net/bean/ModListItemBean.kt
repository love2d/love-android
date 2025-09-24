package org.love2d.android.net.bean

import android.os.Parcelable
import com.squareup.moshi.JsonClass
import kotlinx.parcelize.Parcelize
import org.love2d.android.util.TimeUtil

@JsonClass(generateAdapter = true)
@Parcelize
data class ModListItemBean(
    var isLocal: Boolean = true,
    val installPath: String = "",
    val isFolder : Boolean = true,
    val author: String = "System",
    val cover: String = "",
    val author_avatar_url: String,
    val created_at: String = TimeUtil.timestampToTime(System.currentTimeMillis()),
    val description: String = "",
    val downloaded_time: String = "",
    val game_name: String = "",
    val github_repo_url: String = "",
    val id: String = "",
    val name: String = "",
    val repo_id: Int = 0,
    val stars: String = "0",
    var updated_at: String = TimeUtil.timestampToTime(System.currentTimeMillis()),
    val version: String = "0.0.0",
) : Parcelable