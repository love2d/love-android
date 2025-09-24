package org.love2d.android.room.download

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import kotlinx.coroutines.flow.Flow

/**
 * ClassName DownloadInfoDao
 * Description
 * Create by hjr
 * Date 2025/7/3 10:57
 */
@Dao
interface DownloadInfoDao {
    /** 插入单个 下载条目，存在相同 room_id 会替换 */
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(downloadInfo: DownloadInfo): Long

    /** 更新已有的 mod（通过 room_id） */
    @Update
    suspend fun update(downloadInfo: DownloadInfo)

    /** 删除某个 mod */
    @Delete
    suspend fun delete(downloadInfo: DownloadInfo)

    /** 删除所有 */
    @Query("DELETE FROM download_list")
    suspend fun deleteAll()

    /** 获取所有 mod（按 room_id 降序） */
    @Query("SELECT * FROM download_list ORDER BY room_id DESC")
    fun getAll(): Flow<List<DownloadInfo>>

    @Query("SELECT * FROM download_list ORDER BY room_id DESC")
    suspend fun getAll2List() : List<DownloadInfo>

    /** 根据 room_id 查询 */
    @Query("SELECT * FROM download_list WHERE room_id = :roomId LIMIT 1")
    suspend fun getByRoomId(roomId: Int): DownloadInfo?

    /** 根据业务 ID（mod id）查询 */
    @Query("SELECT * FROM download_list WHERE id = :modId LIMIT 1")
    suspend fun getByModId(modId: String): DownloadInfo?

    /** 判断是否存在指定业务 ID */
    @Query("SELECT EXISTS(SELECT 1 FROM download_list WHERE id = :modId)")
    suspend fun existsByModId(modId: String): Boolean

    @Query("SELECT * FROM download_list ORDER BY CAST(downloaded_time AS INTEGER) DESC")
    fun getAllOrderByDownloadCountDesc(): Flow<List<DownloadInfo>>

    @Query("SELECT * FROM download_list ORDER BY CAST(stars AS INTEGER) DESC")
    fun getAllOrderByStarsDesc(): Flow<List<DownloadInfo>>

    @Query("SELECT * FROM download_list WHERE name LIKE '%' || :keyword || '%' ORDER BY name")
    fun searchByName(keyword: String): Flow<List<DownloadInfo>>
}