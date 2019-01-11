//
//  LuaTest.cpp
//  luaApp
//
//  Created by HW on 2019/1/11.
//  Copyright © 2019 meitu. All rights reserved.
//

#include "LuaTest.hpp"
#include "lua.hpp"
#include <string>
#include "PublicFuncByiOS.h"

void CPP_Call_Lua() {
    std::string bundlePath = AppBundlePath();
    bundlePath += "/add.lua";
    
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    
    int error;
    
    error = luaL_dofile(l, bundlePath.c_str());
    if (error) {
        printf("luaL_dofile error: %d\n", error);
    }
    
    lua_getglobal(l, "add_lua");
    lua_pushnumber(l, 3);
    lua_pushnumber(l, 7);
    
    error = lua_pcall(l, 2, 1, 0);
    if (error) {
        printf("lua_pcall error: %d\n", error);
    }
    
    long result = lua_tointeger(l, 1);
    printf("result = %ld", result);
    
    lua_close(l);
}
