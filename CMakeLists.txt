cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(multith)

find_package(Threads)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses)

add_executable(multith ./src/main.cpp ./src/printer/printer.cpp)

target_link_libraries(multith ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES})
