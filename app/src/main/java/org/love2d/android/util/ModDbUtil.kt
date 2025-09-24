package org.love2d.android.util

import android.content.Context
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.withContext
import org.love2d.android.room.mod.ModDatabase
import org.love2d.android.room.mod.ModInfo
import org.love2d.android.room.mod.ModInfoDao

/**
 * ClassName ModDbUtil
 * Description
 * Create by hjr
 * Date 2025/6/25 15:33
 */
object ModDbUtil {
    private lateinit var db: ModDatabase

    fun init(context: Context) {
        if (!::db.isInitialized) {
            db = ModDatabase.getInstance(context)
        }
    }

    fun getModInfoDao(): ModInfoDao {
        checkInitialized()
        return db.modInfoDao()
    }

    suspend fun getAllMods(): Flow<List<ModInfo>> {
        checkInitialized()
        return withContext(Dispatchers.IO) {
            db.modInfoDao().getAll()
        }
    }

    suspend fun pathMods(installPath: String): Flow<List<ModInfo>> {
        checkInitialized()
        return withContext(Dispatchers.IO) {
            db.modInfoDao().getAllByInstallPathFlow(installPath)
        }
    }

    suspend fun insertMod(mod: ModInfo) {
        checkInitialized()
        withContext(Dispatchers.IO) {
            db.modInfoDao().insert(mod)
        }
    }

    suspend fun deleteMod(mod: ModInfo) {
        checkInitialized()
        withContext(Dispatchers.IO) {
            db.modInfoDao().delete(mod)
        }
    }

    suspend fun updateMod(mod: ModInfo) {
        checkInitialized()
        withContext(Dispatchers.IO) {
            db.modInfoDao().update(mod)
        }
    }

    suspend fun deletePathMods(installPath: String) {
        checkInitialized()
        withContext(Dispatchers.IO) {
            db.modInfoDao().deleteByInstallPath(installPath)
        }
    }

    private fun checkInitialized() {
        if (!ModDbUtil::db.isInitialized) {
            throw IllegalStateException("GameDbUtil is not initialized. Call GameDbUtil.init(context) first.")
        }
    }
}