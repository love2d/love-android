package org.love2d.android.room.download

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import org.love2d.android.DatabaseConfig
import org.love2d.android.room.mod.ModDatabase
import org.love2d.android.room.mod.ModInfo
import org.love2d.android.room.mod.ModInfoDao

/**
 * ClassName DownloadDatabase
 * Description
 * Create by hjr
 * Date 2025/7/3 10:56
 */
@Database(
    entities = [DownloadInfo::class],
    version = DatabaseConfig.DATABASE_VERSION,
    exportSchema = false
)
abstract class DownloadDatabase : RoomDatabase() {

    abstract fun downloadInfoDao(): DownloadInfoDao

    companion object {
        @Volatile
        private var INSTANCE: DownloadDatabase? = null

        fun getInstance(context: Context): DownloadDatabase {
            return INSTANCE ?: synchronized(this) {
                val instance = Room.databaseBuilder(
                    context.applicationContext,
                    DownloadDatabase::class.java,
                    "download_database"
                ).build()
                INSTANCE = instance
                instance
            }
        }
    }
}