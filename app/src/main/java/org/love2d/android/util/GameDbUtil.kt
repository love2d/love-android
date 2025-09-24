package org.love2d.android.util

import android.content.Context
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.withContext
import org.love2d.android.room.game.GameDao
import org.love2d.android.room.game.GameDatabase
import org.love2d.android.room.game.GameInfo

object GameDbUtil {

    private lateinit var db: GameDatabase

    fun init(context: Context) {
        if (!::db.isInitialized) {
            db = GameDatabase.getInstance(context)
        }
    }

    fun getGameDao(): GameDao {
        checkInitialized()
        return db.gameDao()
    }

    fun getAllGames(): Flow<List<GameInfo>> {
        checkInitialized()
        return db.gameDao().getAllGames()
    }

    suspend fun getGameById(id: String): GameInfo? {
        checkInitialized()
        return withContext(Dispatchers.IO) {
            db.gameDao().getGameById(id)
        }
    }

    suspend fun insertGame(game: GameInfo) {
        checkInitialized()
        withContext(Dispatchers.IO) {
            db.gameDao().insertGame(game)
        }
    }

    suspend fun updateGame(game: GameInfo) {
        checkInitialized()
        withContext(Dispatchers.IO) {
            db.gameDao().updateGame(game)
        }
    }

    suspend fun deleteGame(game: GameInfo) {
        checkInitialized()
        withContext(Dispatchers.IO) {
            db.gameDao().deleteGame(game)
        }
    }

    suspend fun deleteAllGames() {
        checkInitialized()
        withContext(Dispatchers.IO) {
            db.gameDao().deleteAllGames()
        }
    }

    private fun checkInitialized() {
        if (!::db.isInitialized) {
            throw IllegalStateException("GameDbUtil is not initialized. Call GameDbUtil.init(context) first.")
        }
    }
}
