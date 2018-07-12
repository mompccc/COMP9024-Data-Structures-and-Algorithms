cmake_minimum_required(VERSION 3.8)
project(new)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c studentRecord.c studentLL.c)
add_executable(new ${SOURCE_FILES})