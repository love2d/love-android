package org.love2d.android.room.download

import android.os.Parcelable
import androidx.room.Entity
import androidx.room.Ignore
import androidx.room.PrimaryKey
import com.squareup.moshi.JsonClass
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.parcelize.Parcelize
import org.love2d.android.util.TimeUtil

/**
 * ClassName DownloadInfo
 * Description
 * Create by hjr
 * Date 2025/7/3 10:54
 */
@JsonClass(generateAdapter = true)
@Entity(tableName = "download_list")
@Parcelize
data class DownloadInfo(
    @PrimaryKey(autoGenerate = true) val room_id: Int = 0,
    var isLocal: Boolean = false,
    var downloadPath : String = "",
    var file_path : String = "",
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
