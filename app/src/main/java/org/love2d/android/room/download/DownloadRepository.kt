package org.love2d.android.room.download

import kotlinx.coroutines.flow.Flow


/**
 * ClassName ModRepository
 * Description
 * Create by hjr
 * Date 2025/6/25 15:22
 */
class DownloadRepository(private val dao: DownloadInfoDao) {

    suspend fun insertDownload(mod: DownloadInfo): Long {
        return dao.insert(mod)
    }

    suspend fun updateDownload(mod: DownloadInfo) {
        dao.update(mod)
    }

    suspend fun deleteDownload(mod: DownloadInfo) {
        dao.delete(mod)
    }

    suspend fun deleteAllDownload() {
        dao.deleteAll()
    }

    fun getAllDownload(): Flow<List<DownloadInfo>> {
        return dao.getAll()
    }

    suspend fun getAllDownloadList(): List<DownloadInfo> {
        return dao.getAll2List()
    }

    suspend fun getDownloadByRoomId(roomId: Int): DownloadInfo? {
        return dao.getByRoomId(roomId)
    }

    suspend fun getDownloadByModId(modId: String): DownloadInfo? {
        return dao.getByModId(modId)
    }

    suspend fun existsModByModId(modId: String): Boolean {
        return dao.existsByModId(modId)
    }

    /** 按星星数量降序获取所有 */
    fun getAllByStarsDesc(): Flow<List<DownloadInfo>> {
        return dao.getAllOrderByStarsDesc()
    }

    /** 按下载次数降序获取所有 */
    fun getAllByDownloadCountDesc(): Flow<List<DownloadInfo>> {
        return dao.getAllOrderByDownloadCountDesc()
    }

    /** 模糊搜索模组名称 */
    fun searchByName(keyword: String): Flow<List<DownloadInfo>> {
        return dao.searchByName(keyword)
    }
}
