package org.love2d.android.room.mod

/**
 * ClassName ModDao
 * Description
 * Create by hjr
 * Date 2025/6/25 15:19
 */
import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.OnConflictStrategy
import androidx.room.Query
import androidx.room.Update
import kotlinx.coroutines.flow.Flow

@Dao
interface ModInfoDao {
    /** 根据 installPath 查询所有 mod（不唯一） */
    @Query("SELECT * FROM mod_list WHERE installPath = :installPath")
    fun getAllByInstallPathFlow(installPath: String): Flow<List<ModInfo>>

    @Query("SELECT * FROM mod_list WHERE installPath = :installPath")
    suspend fun getAllByInstallPath(installPath: String): List<ModInfo>

    /** 插入单个 mod，存在相同 room_id 会替换 */
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(mod: ModInfo): Long

    @Query("SELECT * FROM mod_list WHERE installPath = :installPath AND id = :modId LIMIT 1")
    suspend fun getModInPath(installPath: String, modId: String): ModInfo?

    /** 批量插入多个 mod */
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertAll(mods: List<ModInfo>)

    /** 更新已有的 mod（通过 room_id） */
    @Update
    suspend fun update(mod: ModInfo)

    /** 删除某个 mod */
    @Delete
    suspend fun delete(mod: ModInfo)

    /** 删除指定 installPath 的所有 mod */
    @Query("DELETE FROM mod_list WHERE installPath = :installPath")
    suspend fun deleteByInstallPath(installPath: String)

    /** 根据 room_id 删除 */
    @Query("DELETE FROM mod_list WHERE room_id = :roomId")
    suspend fun deleteByRoomId(roomId: Int)

    /** 删除所有 */
    @Query("DELETE FROM mod_list")
    suspend fun deleteAll()

    /** 获取所有 mod（按 room_id 降序） */
    @Query("SELECT * FROM mod_list ORDER BY room_id DESC")
    fun getAll(): Flow<List<ModInfo>>

    /** 根据 room_id 查询 */
    @Query("SELECT * FROM mod_list WHERE room_id = :roomId LIMIT 1")
    suspend fun getByRoomId(roomId: Int): ModInfo?

    /** 根据业务 ID（mod id）查询 */
    @Query("SELECT * FROM mod_list WHERE id = :modId LIMIT 1")
    suspend fun getByModId(modId: String): ModInfo?

    /** 判断是否存在指定业务 ID */
    @Query("SELECT EXISTS(SELECT 1 FROM mod_list WHERE id = :modId)")
    suspend fun existsByModId(modId: String): Boolean

    @Query("SELECT EXISTS(SELECT 1 FROM mod_list WHERE installPath = :installPath AND id = :modId)")
    suspend fun existsByInstallPathAndModId(installPath: String, modId: String): Boolean

}