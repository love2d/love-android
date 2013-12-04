//
//  main.cpp
//  SDLTutorial
//
//  Created by Ciaran McCormack on 25/09/13.
//  Copyright (c) 2013 Raiblin. All rights reserved.
//

#include <iostream>
#include <SDL.h>
#include <SDL_opengles.h>
#include <memory>

#ifdef __cplusplus
extern "C" {
#endif
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#ifdef __cplusplus
}
#endif

using namespace std;

class Graphics;

shared_ptr<Graphics> graphics;

class Graphics
{
public:
	float color[3];

	Graphics() :
		color ({ rand() % 255 / 255.0f, rand() % 255 / 255.0f, rand() % 255 / 255.0f})
		{}

    void update()
    {
        glClearColor(color[0], color[1], color[2], 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
};

int l_get_color (lua_State *L) {
	lua_pushnumber (L, graphics->color[0]);
	lua_pushnumber (L, graphics->color[1]);
	lua_pushnumber (L, graphics->color[2]);

	return 3;
}

int l_set_color(lua_State *L) {
	SDL_Log ("[Lua] setcolor was called");

	if (lua_gettop(L) != 3) {
		SDL_Log ("[Lua] engine.setcolor error: invalid color");
		return 0;
	}

	float r = 0.f;
	if (!lua_isnumber(L, -3)) {
		SDL_Log("[Lua] engine.set_color error: invalid color");
		return 0;
	}
	r = (float) lua_tonumber (L, -3);

	float g = 0.f;
	if (!lua_isnumber(L, -2)) {
		SDL_Log("[Lua] engine.set_color error: invalid color");
		return 0;
	}
	g = (float) lua_tonumber (L, -2);

	float b = 0.f;
	if (!lua_isnumber(L, -1)) {
		SDL_Log("[Lua] engine.set_color error: invalid color");
		return 0;
	}
	b = (float) lua_tonumber (L, -1);

	SDL_Log ("[Lua] got color %f, %f, %f", r, g, b );

	graphics->color[0] = r;
	graphics->color[1] = g;
	graphics->color[2] = b;

	return 0;
}

int l_log (lua_State *L) {
	if (!lua_isstring(L, -1)) {
		SDL_Log ("[Lua] invalid error message: expected string");
		return 0;
	}
	SDL_Log ("[Lua] %s", lua_tostring (L, -1));
	return 0;
}

static const struct luaL_Reg enginelib[] = {
		{"get_color", l_get_color},
		{"set_color", l_set_color},
		{"log", l_log},
		{NULL, NULL}
};

int EventFilter(void* userdata, SDL_Event* event)
{
    switch (event->type)
    {
        case SDL_KEYDOWN:
            SDL_Log("Key Down %d", event->key.keysym.sym);
            return 0;

        case SDL_KEYUP:
            SDL_Log("Key Up %d", event->key.keysym.sym);
            return 0;

        case SDL_MOUSEMOTION:
            SDL_Log("Mouse Moved. X=%d, Y=%d, RelativeX=%d, RelativeY=%d", event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
            return 0;

        case SDL_MOUSEBUTTONDOWN:
            SDL_Log("Mouse Button Down %d", event->button.button);
            return 0;

        case SDL_MOUSEBUTTONUP:
            SDL_Log("Mouse Button Up %d", event->button.button);
            return 0;

        case SDL_MOUSEWHEEL:
            SDL_Log("Mouse Wheel");
            return 0;
    }

    return 1;
}

void l_call_on_touch (lua_State *L, int x, int y) {
	lua_getglobal (L, "on_touch");

	if (lua_isfunction(L, -1)) {
		lua_pushnumber (L, x);
		lua_pushnumber (L, y);
		lua_pcall (L, 2, 0, 0);
	}
}

void l_call_update (lua_State *L, float dt) {
	lua_getglobal (L, "update");
	if (lua_isfunction(L, -1)) {
		lua_pushnumber (L, dt);
		lua_pcall (L, 1, 0, 0);
	}
}

int main(int argc, char * argv[])
{
    int width = 1080;
    int height = 720;

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
        return 0;
    }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //Create the window
    auto window = SDL_CreateWindow("SDL 2.0 OSX Tutorial", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (window == 0)
    {
        SDL_Quit();
        return false;
    }

    auto gl = SDL_GL_CreateContext(window);

    SDL_AddEventWatch(EventFilter, nullptr);

    graphics = shared_ptr<Graphics>(new Graphics());

    SDL_Log ("OpenGL Version: %s", glGetString(GL_VERSION));

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_register (L, "engine", enginelib);

    SDL_RWops *file = SDL_RWFromFile("testfile.lua", "rb");
    if (file) {
        Sint64 file_size = file->size(file);
        char data_buffer[file_size + 1];
        size_t read_bytes = file->read(file, data_buffer, sizeof(char), (size_t) file_size);
        data_buffer[read_bytes] = '\0';
        luaL_dostring(L, data_buffer);
    } else {
    	SDL_Log ("could not open file");
    }

    unsigned int last_time = SDL_GetTicks();

    //Game Loop
    SDL_Event event;
    auto done = false;
    while (!done)
    {
        SDL_PumpEvents();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_APP_DIDENTERFOREGROUND:
                    SDL_Log("SDL_APP_DIDENTERFOREGROUND");
                    break;

                case SDL_APP_DIDENTERBACKGROUND:
                    SDL_Log("SDL_APP_DIDENTERBACKGROUND");
                    break;

                case SDL_APP_LOWMEMORY:
                    SDL_Log("SDL_APP_LOWMEMORY");
                    break;

                case SDL_APP_TERMINATING:
                    SDL_Log("SDL_APP_TERMINATING");
                    break;

                case SDL_APP_WILLENTERBACKGROUND:
                    SDL_Log("SDL_APP_WILLENTERBACKGROUND");
                    break;

                case SDL_APP_WILLENTERFOREGROUND:
                    SDL_Log("SDL_APP_WILLENTERFOREGROUND");
                    break;

                case SDL_FINGERDOWN:
                	l_call_on_touch(L, event.tfinger.x, event.tfinger.y);
                	SDL_Log("Got finger down at %d,%d", event.tfinger.x, event.tfinger.y);
                	break;

                case SDL_WINDOWEVENT:
                {
                    switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_SHOWN:
                            SDL_Log("Window %d shown", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_HIDDEN:
                            SDL_Log("Window %d hidden", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_EXPOSED:
                            SDL_Log("Window %d exposed", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_MOVED:
                            SDL_Log("Window %d moved to %d,%d", event.window.windowID, event.window.data1, event.window.data2);
                            break;
                        case SDL_WINDOWEVENT_RESIZED:
                            SDL_Log("Window %d resized to %dx%d", event.window.windowID, event.window.data1, event.window.data2);
                            break;
                        case SDL_WINDOWEVENT_MINIMIZED:
                            SDL_Log("Window %d minimized", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_MAXIMIZED:
                            SDL_Log("Window %d maximized", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_RESTORED:
                            SDL_Log("Window %d restored", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_ENTER:
                            SDL_Log("Mouse entered window %d", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_LEAVE:
                            SDL_Log("Mouse left window %d", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_FOCUS_GAINED:
                            SDL_Log("Window %d gained keyboard focus", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_FOCUS_LOST:
                            SDL_Log("Window %d lost keyboard focus", event.window.windowID);
                            break;
                        case SDL_WINDOWEVENT_CLOSE:
                            SDL_Log("Window %d closed", event.window.windowID);
                            break;
                        default:
                            SDL_Log("Window %d got unknown event %d", event.window.windowID, event.window.event);
                            break;
                    }

                    break;
                }
            }
        }

        unsigned int current_time = SDL_GetTicks();
        l_call_update(L, static_cast<float>(current_time - last_time) * 0.001f);
        last_time = current_time;

        graphics->update();
        SDL_GL_SwapWindow(window);
    }

    lua_close (L);

    SDL_GL_DeleteContext(gl);

    // Done! Close the window, clean-up and exit the program.
    SDL_DestroyWindow(window);
    SDL_Quit();
}

