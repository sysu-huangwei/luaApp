//
//  LuaTest.cpp
//  luaApp
//
//  Created by HW on 2019/1/11.
//  Copyright © 2019 meitu. All rights reserved.
//

#include "LuaTest.hpp"
#include "lua.hpp"
#include "Log.h"


static const char* CPP_Call_Lua_str =
"print(\"Hello World!\");  \n \
name = \"huangwei\"  \n \
age = 18  \n \
company = {name = \"meitu\", department = \"bct\"}  \n \
function add_lua(a, b)  \n \
return a + b;  \n \
end;  \n ";


static const char* Lua_Call_CPP_str =
"a = 3  \n \
b = 7  \n \
c = 5  \n \
sum = add_CPP(a,b,c)  \n \
print(\"sum = \",sum)  \n ";

void CPP_Call_Lua() {
    //所有lua API的调用之前都要创建一个lua state
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);//加载lua基本库
    
    int error;
    //打开并解释运行一个lua脚本
    error = luaL_dostring(l, CPP_Call_Lua_str);
    if (error) {
        LOGE("luaL_dofile error: %d", error);
    }

    // 通过lua_getglobal方法把lua脚本内指定名称的变量压入栈顶
    // lua虚拟栈索引从1或-1开始
    // 索引 1 栈底第 1 个元素，  索引 2 栈底第 2 个元素...
    // 索引 -1 栈顶第 1 个元素，  索引 -2 栈顶第 2 个元素...
    // 一般直接索引-1来拿栈顶元素
    
    //读取字符串
    lua_getglobal(l, "name");
    const char* name = lua_tostring(l, -1);
    LOGI("name = %s", name);
    
    //读取数字
    lua_getglobal(l, "age");
    long age = lua_tointeger(l, -1);
    LOGI("age = %ld", age);

    //把表压栈的时候，会把表的所有元素按顺序压栈，表的第一个元素会在栈顶
    //读取表
    lua_getglobal(l, "company");
    lua_getfield(l, -1, "name");
    const char* companyName = lua_tostring(l, -1);
    LOGI("companyName = %s", companyName);
    lua_getfield(l, -2, "department");
    const char* department = lua_tostring(l, -1);
    LOGI("department = %s", department);
    
    //修改表的元素
    lua_pushstring(l, "O2Cam");
    lua_setfield(l, -4, "App");//TODO:这里为什么是-4和-3 ？
    lua_getfield(l, -3, "App");
    const char* App = lua_tostring(l, -1);
    LOGI("App = %s", App);
    
    //调用lua的方法，方法的返回值会压入栈顶
    lua_getglobal(l, "add_lua");
    lua_pushnumber(l, 3);//如果方法有参数，也要把参数依次压栈
    lua_pushnumber(l, 7);
    
    error = lua_pcall(l, 2, 1, 0);//2:参数个数 1:返回值个数 0:错误处理函数在栈中的索引，0表示没有
    if (error) {
        LOGE("lua_pcall error: %d", error);
    }
    //从栈顶取lua函数的返回值
    long result = lua_tointeger(l, -1);
    LOGI("result = %ld", result);
    
    lua_close(l);
}


int add_CPP(lua_State *l) {
    //获取参数个数
    int n = lua_gettop(l);
    
    double sum = 0;
    for (int i = 1; i <= n; i++) {
        //获取参数个数之后，栈顶开始连续n个元素都是参数，使用索引取出来
        double num = lua_tonumber(l, -i);
        sum += num;
    }
    
    //把计算结果压栈，这样lua才能获取到
    lua_pushnumber(l, sum);
    
    //返回值的个数
    return 1;
}

void Lua_Call_CPP() {
    //所有lua API的调用之前都要创建一个lua state
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);//加载lua基本库
    
    //向lua注册函数，这样lua脚本就可以找到这个名字的C函数
    lua_register(l, "add_CPP", add_CPP);
    
    int error;
    //打开并解释运行一个lua脚本
    error = luaL_dostring(l, Lua_Call_CPP_str);
    if (error) {
        LOGE("luaL_dofile error: %d", error);
    }
    
    //结果值
    lua_getglobal(l, "sum");
    long result = lua_tointeger(l, -1);
    LOGI("result = %ld", result);
    
    lua_close(l);
}
