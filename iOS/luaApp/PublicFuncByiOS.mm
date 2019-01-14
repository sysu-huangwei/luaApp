//
//  PublicFuncByiOS.m
//  luaApp
//
//  Created by HW on 2019/1/11.
//  Copyright © 2019 meitu. All rights reserved.
//

#import "PublicFuncByiOS.h"
#import <Foundation/Foundation.h>

char* AppBundlePath() {
    NSString* bundlePath = [[NSBundle mainBundle] bundlePath];
    return (char*)[bundlePath UTF8String];
}
