cmake_minimum_required(VERSION 3.27)
project(Display)

set(CMAKE_CXX_STANDARD 17)

#Try sudo apt install libncurses-dev if not installed
#sudo apt-get install libncursesw5-dev
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Display main.cpp
        constants.h
        Display.cpp
        Display.h)
target_link_libraries(Display ${CURSES_LIBRARIES})

