#include <jni.h>
#include "LuaTest.hpp"

#define CLASS_NAME_PATH "com/meitu/MainActivity"

class LuaTestJni {
public:

    static void nCPP_Call_Lua(JNIEnv *env, jobject obj) {
        CPP_Call_Lua();
    }

    static void nLua_Call_CPP(JNIEnv *env, jobject obj) {
        Lua_Call_CPP();
    }
};

static JNINativeMethod methods[] = {
        {"native_CPP_Call_Lua", "()V", (void *) LuaTestJni::nCPP_Call_Lua},
        {"native_Lua_Call_CPP", "()V", (void *) LuaTestJni::nLua_Call_CPP},
};


int registerLuaTestJniMethods(JNIEnv *env, void *reserved) {
    jclass cls = env->FindClass(CLASS_NAME_PATH);
    if (cls == NULL) {
        return JNI_ERR;
    }

    jint nRes = env->RegisterNatives(cls, methods, sizeof(methods) / sizeof(methods[0]));
    if (nRes < 0) {
        return JNI_ERR;
    }

    return JNI_OK;
}