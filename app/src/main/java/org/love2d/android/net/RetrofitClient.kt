package org.love2d.android.net

import android.util.Log
import androidx.compose.runtime.MutableState
import kotlinx.coroutines.flow.MutableStateFlow
import okhttp3.OkHttpClient
import okhttp3.logging.HttpLoggingInterceptor
import org.love2d.android.Net.BASE_URL
import retrofit2.Retrofit
import retrofit2.converter.moshi.MoshiConverterFactory

object RetrofitClient {
    private val logging = HttpLoggingInterceptor().apply {
        level = HttpLoggingInterceptor.Level.BODY
    }

    private val okHttpClient = OkHttpClient.Builder()
        .addInterceptor(logging)
        .build()

    val api: HApiService by lazy {
        Retrofit.Builder()
            .baseUrl(BASE_URL)
            .client(okHttpClient)
            .addConverterFactory(MoshiConverterFactory.create()) // 可换 Gson
            .build()
            .create(HApiService::class.java)
    }

    suspend fun <T> loadWithUiState(
        uiState: MutableStateFlow<UiState<T>>,
        block: suspend () -> T
    ) {
        uiState.value = UiState.Loading
        try {
            uiState.value = UiState.Success(block())
            Log.d("HJR-NET", "Success")
        } catch (e: Exception) {
            Log.e("HJR-NET", e.message ?: "Unknown error")
            uiState.value = UiState.Error(e.message ?: "Unknown error")
        }
    }
}

sealed interface UiState<out T> {
    object Loading : UiState<Nothing>
    data class Success<T>(val data: T) : UiState<T>
    data class Error(val message: String) : UiState<Nothing>
}