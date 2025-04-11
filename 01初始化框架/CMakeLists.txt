cmake_minimum_required(VERSION 3.10)

# 项目名称（按需修改）
project(8051_Project)

# 设置 C 标准为 C17（需编译器支持）
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置编译选项（示例：调试模式）
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# 查找所有源文件（确保 src 目录存在且包含 .c 文件）
file(GLOB_RECURSE SOURCES "src/*.c")

# 添加头文件搜索路径（确保 include 目录存在）
include_directories(include)

# 生成可执行文件（如果 SOURCES 为空会报错）
add_executable(${PROJECT_NAME} ${SOURCES})

# 设置输出目录为项目根目录下的 bin（自动创建目录）
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})