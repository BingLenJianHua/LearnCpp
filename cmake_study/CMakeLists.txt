# 1. 指定 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 给项目起个名字
project(MyCalcProject)

# 3. 指定 C++ 标准 (比如 C++11 或 17)
set(CMAKE_CXX_STANDARD 1)

# 4. 核心指令：把哪些源文件编译成可执行文件？
# 语法：add_executable(最终程序名 源文件1 源文件2 ...)
add_executable(app main.cpp calc.cpp)