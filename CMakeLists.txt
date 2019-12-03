cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(multith)

find_package(Threads)

add_executable(multith ./src/main.cpp)

target_link_libraries(multith ${CMAKE_THREAD_LIBS_INIT})
