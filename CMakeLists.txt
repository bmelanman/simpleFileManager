cmake_minimum_required(VERSION 3.23)
project(file_manager)

set(CMAKE_CXX_STANDARD 14)

add_library(FileSys lib/FileSys.c lib/FileSys.h)
#add_library(Stack lib/Stack.c lib/Stack.h)
add_library(zVector lib/zvector/src/zvector.c lib/zvector/src/zvector.h)

add_executable(file_manager src/main.c src/main.h)

target_link_libraries(file_manager FileSys zVector)
