
cmake_minimum_required(VERSION 3.4.1)

# 设置变量，表示库名字
set(MY_LIBRARY_NAME lua)


# 头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/../../liblua/include/lua
    ${PROJECT_SOURCE_DIR}/../../src
    ${PROJECT_SOURCE_DIR}/src/main/cpp
)


# 设置变量，表示所有的源文件
# General source files
file(
    GLOB SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/../../src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/main/cpp/*.cpp
)


# 需要的库文件所在的目录
link_directories(
    ${PROJECT_SOURCE_DIR}/../../liblua/lib/android/armeabi-v7a
)


# 生成的库文件
add_library(${MY_LIBRARY_NAME} SHARED ${SOURCE_FILES})


# 需要链接的库文件
target_link_libraries(
    lua
    liblua.a
    log
)