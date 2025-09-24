// 文件: lovely_primitives.h

#ifndef LOVELY_PRIMITIVES_H
#define LOVELY_PRIMITIVES_H

#include <stdint.h>
#include "lua.h" // 包含官方头文件以获取 lua_State 的定义

// 手动定义 LuaLib 结构体，并使用官方的 lua_State 类型
typedef struct LuaLib {
    void (*lua_call)(lua_State *state, int32_t nargs, int32_t nresults);
    int32_t (*lua_pcall)(lua_State *state, int32_t nargs, int32_t nresults, int32_t errfunc);
    void (*lua_getfield)(lua_State *state, int32_t index, const char *k);
    void (*lua_setfield)(lua_State *state, int32_t index, const char *k);
    int32_t (*lua_gettop)(lua_State *state);
    void (*lua_settop)(lua_State *state, int32_t index);
    void (*lua_pushvalue)(lua_State *state, int32_t index);
    void (*lua_pushcclosure)(lua_State *state, int (*f)(lua_State*), int32_t n);
    const char *(*lua_tolstring)(lua_State *state, int32_t index, uintptr_t *len);
} LuaLib;

#endif // LOVELY_PRIMITIVES_H