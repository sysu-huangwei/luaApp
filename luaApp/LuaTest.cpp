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
    //所有lua API的调用之前都要创建一个lua state
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);//加载lua基本库
    
    std::string bundlePath = AppBundlePath();
    bundlePath += "/CPP_Call_Lua.lua";
    
    int error;
    //打开并解释运行一个lua脚本
    error = luaL_dofile(l, bundlePath.c_str());
    if (error) {
        printf("luaL_dofile error: %d\n", error);
    }

    // 通过lua_getglobal方法把lua脚本内指定名称的变量压入栈顶
    // lua虚拟栈索引从1或-1开始
    // 索引 1 栈底第 1 个元素，  索引 2 栈底第 2 个元素...
    // 索引 -1 栈顶第 1 个元素，  索引 -2 栈顶第 2 个元素...
    // 一般直接索引-1来拿栈顶元素
    
    //读取字符串
    lua_getglobal(l, "name");
    const char* name = lua_tostring(l, -1);
    printf("name = %s\n", name);
    
    //读取数字
    lua_getglobal(l, "age");
    long age = lua_tointeger(l, -1);
    printf("age = %ld\n", age);

    //把表压栈的时候，会把表的所有元素按顺序压栈，表的第一个元素会在栈顶
    //读取表
    lua_getglobal(l, "company");
    lua_getfield(l, -1, "name");
    const char* companyName = lua_tostring(l, -1);
    printf("companyName = %s\n", companyName);
    lua_getfield(l, -2, "department");
    const char* department = lua_tostring(l, -1);
    printf("department = %s\n", department);
    
    //修改表的元素
    lua_pushstring(l, "O2Cam");
    lua_setfield(l, -4, "App");//TODO:这里为什么是-4和-3 ？
    lua_getfield(l, -3, "App");
    const char* App = lua_tostring(l, -1);
    printf("App = %s\n", App);
    
    //调用lua的方法，方法的返回值会压入栈顶
    lua_getglobal(l, "add_lua");
    lua_pushnumber(l, 3);//如果方法有参数，也要把参数依次压栈
    lua_pushnumber(l, 7);
    
    error = lua_pcall(l, 2, 1, 0);//2:参数个数 1:返回值个数 0:错误处理函数在栈中的索引，0表示没有
    if (error) {
        printf("lua_pcall error: %d\n", error);
    }
    //从栈顶取lua函数的返回值
    long result = lua_tointeger(l, -1);
    printf("result = %ld\n", result);
    
    lua_close(l);
}
