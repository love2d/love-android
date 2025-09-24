package org.love2d.android.room.mod

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import org.love2d.android.DatabaseConfig

/**
 * ClassName ModDatabase
 * Description
 * Create by hjr
 * Date 2025/6/25 15:21
 */
@Database(
    entities = [ModInfo::class],
    version = DatabaseConfig.DATABASE_VERSION,
    exportSchema = false
)
abstract class ModDatabase : RoomDatabase() {

    abstract fun modInfoDao(): ModInfoDao

    companion object {
        @Volatile
        private var INSTANCE: ModDatabase? = null

        fun getInstance(context: Context): ModDatabase {
            return INSTANCE ?: synchronized(this) {
                val instance = Room.databaseBuilder(
                    context.applicationContext,
                    ModDatabase::class.java,
                    "mod_database"
                ).build()
                INSTANCE = instance
                instance
            }
        }
    }
}
