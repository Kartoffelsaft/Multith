cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(multith)

find_package(Threads REQUIRED)
#find_package(SFML 2 REQUIRED audio graphics window system)
set(SFML_LIBRARIES sfml-graphics sfml-audio sfml-window sfml-system)

add_executable(multith 
    ./src/main.cpp 
    ./src/printer/printer.cpp 
    ./src/tickCoordinator/tickCoordinator.cpp
    ./src/physicsModel/physicsModel.cpp
    ./src/physicsModel/physicsModelPrintable.cpp
)

target_link_libraries(multith ${CMAKE_THREAD_LIBS_INIT} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
