// 文件: luajit/src/lovely_jni_bridge.cpp

#include <jni.h>

// 使用 extern "C" 将所有 C 语言相关的部分包裹起来
// 这样 C++ 编译器就会使用 C 语言的规则（不修改函数名）来处理它们
extern "C" {

#include "lua.h"
#include "lauxlib.h"
#include "lovely_ffi.h"

// 声明我们在 lj_load.c 中重命名的原始函数
int original_luaL_loadbufferx(lua_State *L, const char *buf, size_t size,
        const char *name, const char *mode);

// 这是一个辅助函数，用于填充 Rust 需要的 LuaLib 结构体
// 将它也放在 extern "C" 内部，确保它生成的代码是 C 兼容的
static LuaLib get_lua_api_pointers() {
    LuaLib lib;
    lib.lua_call = lua_call;
    lib.lua_pcall = lua_pcall;
    lib.lua_getfield = lua_getfield;
    lib.lua_setfield = lua_setfield;
    lib.lua_gettop = lua_gettop;
    lib.lua_settop = lua_settop;
    lib.lua_pushvalue = lua_pushvalue;
    lib.lua_pushcclosure = lua_pushcclosure;
    lib.lua_tolstring = lua_tolstring;
    return lib;
}

// JNI 函数本身也用 extern "C"
//org/love2d/android/GameActivity.java
JNIEXPORT void JNICALL
Java_org_love2d_android_GameActivity_nativeInitializeLovely(JNIEnv *env, jclass clazz, jstring mod_dir) {
// 1. 从 Java 获取模组目录路径
const char* mod_dir_str = env->GetStringUTFChars(mod_dir, 0);

// 2. 填充 Lua API 函数指针
LuaLib lualib = get_lua_api_pointers();

// 3. 调用 Rust 的初始化函数，将所有信息传递过去
lovely_init(mod_dir_str, (OriginalLoadbufferx)original_luaL_loadbufferx, lualib);

// 4. 释放从 Java 获取的字符串资源
env->ReleaseStringUTFChars(mod_dir, mod_dir_str);
}

} // extern "C" 结束