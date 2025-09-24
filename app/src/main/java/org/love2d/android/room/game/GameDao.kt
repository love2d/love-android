package org.love2d.android.room.game

import androidx.room.*
import kotlinx.coroutines.flow.Flow

@Dao
interface GameDao {

    @Query("SELECT * FROM games ORDER BY lastPlayed DESC")
    fun getAllGames(): Flow<List<GameInfo>>

    @Query("SELECT * FROM games ORDER BY lastPlayed DESC")
    suspend fun getAllGamesNow(): List<GameInfo>

    @Query("SELECT * FROM games WHERE id = :id LIMIT 1")
    suspend fun getGameById(id: String): GameInfo?

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertGame(game: GameInfo)

    @Update
    suspend fun updateGame(game: GameInfo)

    @Delete
    suspend fun deleteGame(game: GameInfo)

    @Query("DELETE FROM games")
    suspend fun deleteAllGames()
}
