package org.love2d.android.net

import okhttp3.ResponseBody
import org.love2d.android.room.download.DownloadInfo
import retrofit2.Response
import retrofit2.http.GET
import retrofit2.http.Query
import retrofit2.http.QueryMap

interface HApiService {

    //获取模组列表
    @GET("/api/list")
    suspend fun getModList(@QueryMap params: Map<String, @JvmSuppressWildcards Any>): PageListApiResponse<DownloadInfo>

    //获取模组详情
    @GET("/api/get_mod_info")
    suspend fun getModInfo(@QueryMap params: Map<String, @JvmSuppressWildcards Any>): ApiResponse<Any>

    //搜索模组
    @GET("/api/search_mod")
    suspend fun searchMod(@QueryMap params: Map<String, @JvmSuppressWildcards Any>): PageListApiResponse<DownloadInfo>

    //下载模组
    @GET("/api/download_mod")
    suspend fun downloadMod(@Query("id") id: String): Response<ResponseBody>
}