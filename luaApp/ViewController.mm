//
//  ViewController.m
//  luaApp
//
//  Created by HW on 2019/1/11.
//  Copyright © 2019 meitu. All rights reserved.
//

#import "ViewController.h"
#include "LuaTest.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    CPP_Call_Lua();
    
}


@end
