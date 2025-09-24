package org.love2d.android.room.mod

import kotlinx.coroutines.flow.Flow


/**
 * ClassName ModRepository
 * Description
 * Create by hjr
 * Date 2025/6/25 15:22
 */
class ModRepository(private val dao: ModInfoDao) {

    suspend fun insertMod(mod: ModInfo): Long {
        return dao.insert(mod)
    }

    suspend fun insertMods(mods: List<ModInfo>) {
        dao.insertAll(mods)
    }

    suspend fun updateMod(mod: ModInfo) {
        dao.update(mod)
    }

    suspend fun getModInPath(installPath: String, modId: String): ModInfo? {
        return dao.getModInPath(installPath, modId)
    }

    suspend fun deleteMod(mod: ModInfo) {
        dao.delete(mod)
    }

    suspend fun deleteModByRoomId(roomId: Int) {
        dao.deleteByRoomId(roomId)
    }

    suspend fun deleteAllMods() {
        dao.deleteAll()
    }

    fun getAllMods(): Flow<List<ModInfo>> {
        return dao.getAll()
    }

    suspend fun getModByRoomId(roomId: Int): ModInfo? {
        return dao.getByRoomId(roomId)
    }

    suspend fun getModByModId(modId: String): ModInfo? {
        return dao.getByModId(modId)
    }

    suspend fun existsModByModId(modId: String): Boolean {
        return dao.existsByModId(modId)
    }

    fun getModsByInstallPathFlow(installPath: String): Flow<List<ModInfo>> {
        return dao.getAllByInstallPathFlow(installPath)
    }

    suspend fun getModsByInstallPath(installPath: String): List<ModInfo> {
        return dao.getAllByInstallPath(installPath)
    }

    suspend fun deleteModsByInstallPath(installPath: String) {
        return dao.deleteByInstallPath(installPath)
    }

    suspend fun existsModInPath(installPath: String, modId: String): Boolean {
        return dao.existsByInstallPathAndModId(installPath, modId)
    }
}
