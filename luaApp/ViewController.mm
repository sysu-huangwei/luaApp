//
//  ViewController.m
//  luaApp
//
//  Created by HW on 2019/1/11.
//  Copyright © 2019 meitu. All rights reserved.
//

#import "ViewController.h"
#include "LuaTest.hpp"
#include "lua.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    NSString *path = [[[NSBundle mainBundle] bundlePath] stringByAppendingPathComponent:@"add.lua"];
    
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    
    int error;
    
    error = luaL_dofile(l, [path UTF8String]);
    if (error) {
        NSLog(@"error!!!!!!!!!!!!!!!!!!!!!!!!");
    }

    lua_getglobal(l, "add_lua");
    lua_pushnumber(l, 3);
    lua_pushnumber(l, 7);
    
    error = lua_pcall(l, 2, 1, 0);
    if (error) {
        NSLog(@"error!!!!!!!!!!!!!!!!!!!!!!!!");
    }
    
    long result = lua_tointeger(l, 1);
    NSLog(@"result = %ld", result);
    
    lua_close(l);
    
    run();
}


@end
