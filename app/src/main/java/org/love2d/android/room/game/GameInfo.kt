package org.love2d.android.room.game

import android.os.Parcelable
import androidx.room.Entity
import androidx.room.PrimaryKey
import kotlinx.parcelize.Parcelize

@Parcelize
@Entity(tableName = "games")
data class GameInfo(
    @PrimaryKey(autoGenerate = true) val id: Int = 0,   // 唯一ID，比如路径、UUID等
    var name: String,
    var filePath: String,
    var modPath : String,
    var iconPath: String? = null,
    var savePath : String,
    var isEnableMod : Boolean = true,
    var createTime : Long = 0L,
    var lastPlayed: Long = 0L
) : Parcelable