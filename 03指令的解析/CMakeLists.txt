cmake_minimum_required(VERSION 3.10)

# 必须在 project() 之前设置这些变量
set(CMAKE_C_COMPILER "D:/4environment/mingw/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/4environment/mingw/mingw64/bin/g++.exe")

# 项目设置
project(8051_Project)

# 标准设置
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# 源文件搜索
file(GLOB_RECURSE SOURCES "src/*.c")

# 头文件路径
include_directories(include)

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 输出目录设置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})