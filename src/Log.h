//
//  Log.h
//  luaApp
//
//  Created by HW on 2019/1/14.
//  Copyright © 2019 meitu. All rights reserved.
//

#ifndef Log_h
#define Log_h

#define LOG_TAG "lua"

#if defined(ANDROID) || defined(__ANDROID__)
//安卓平台
#include <android/log.h>
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__);
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__);
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__);
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__);
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);
#define  LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__);

#else
#include <stdio.h>
//非安卓平台
#define  LOGV(...)  printf("[" LOG_TAG "] VERBOSE:> ");printf(__VA_ARGS__);printf("\n");
#define  LOGD(...)  printf("<[" LOG_TAG "] DEBUG:> ");printf(__VA_ARGS__);printf("\n");
#define  LOGI(...)  printf("<[" LOG_TAG "] INFO:> ");printf(__VA_ARGS__);printf("\n");
#define  LOGW(...)  printf("<[" LOG_TAG "] WARN:> ");printf(__VA_ARGS__);printf("\n");
#define  LOGE(...)  printf("<[" LOG_TAG "] ERROR:> ");printf(__VA_ARGS__);printf("\n");
#define  LOGF(...)  printf("<[" LOG_TAG "] FATAL:> ");printf(__VA_ARGS__);printf("\n");

#endif

#endif /* Log_h */
