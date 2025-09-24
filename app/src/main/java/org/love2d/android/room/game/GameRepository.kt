package org.love2d.android.room.game

import kotlinx.coroutines.flow.Flow

class GameRepository(private val dao: GameDao) {

    val allGames: Flow<List<GameInfo>> = dao.getAllGames()

    suspend fun getGameById(id: String): GameInfo? = dao.getGameById(id)

    suspend fun insertGame(game: GameInfo) = dao.insertGame(game)

    suspend fun updateGame(game: GameInfo) = dao.updateGame(game)

    suspend fun deleteGame(game: GameInfo) = dao.deleteGame(game)

    suspend fun deleteAllGames() = dao.deleteAllGames()
}
