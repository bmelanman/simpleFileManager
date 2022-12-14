cmake_minimum_required(VERSION 3.23)
project(file_manager)

set(CMAKE_CXX_STANDARD 14)

add_executable(file_manager main.c main.h FileSys.c FileSys.h Stack.c Stack.h)
