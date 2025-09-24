#include "lua.h"
#include "lauxlib.h"

// 声明原始函数（你在 lj_load.c 里应该有重命名过）
extern int original_luaL_loadbufferx(lua_State *L,
        const char *buf,
        size_t size,
        const char *name,
        const char *mode);

// 这是 luajit 链接时需要的符号
int lovely_entrypoint_for_luajit(lua_State *L,
        const unsigned char *buf,
        uintptr_t size,
        const unsigned char *name,
        const unsigned char *mode) {
    // 暂时直接转发给原始函数
    return original_luaL_loadbufferx(L,
            (const char*)buf,
            (size_t)size,
            (const char*)name,
            (const char*)mode);
}
