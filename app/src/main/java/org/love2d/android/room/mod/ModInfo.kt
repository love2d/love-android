package org.love2d.android.room.mod

import android.os.Parcelable
import androidx.room.Entity
import androidx.room.PrimaryKey
import kotlinx.parcelize.Parcelize
import org.love2d.android.util.TimeUtil

@Entity(tableName = "mod_list")
@Parcelize
data class ModInfo(
    @PrimaryKey(autoGenerate = true) val room_id: Int = 0,
    var isLocal: Boolean = true,
    var resultName : String = "",
    var installPath: String = "",
    var author: String = "System",
    var cover: String = "",
    var author_avatar_url: String = "",
    var created_at: String = TimeUtil.timestampToTime(System.currentTimeMillis()),
    var description: String = "",
    var downloaded_time: String = "",
    var game_name: String = "",
    var github_repo_url: String = "",
    var id: String = "",
    var name: String = "",
    var from : String = "",
    var repo_id: Int = 0,
    var stars: String = "0",
    var updated_at: String = TimeUtil.timestampToTime(System.currentTimeMillis()),
    var version: String = "0.0.0",
) : Parcelable