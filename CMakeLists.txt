cmake_minimum_required(VERSION 3.13)
project(Display)

set(CMAKE_CXX_STANDARD 17)

#Try sudo apt install libncurses-dev if not installed
#sudo apt-get install libncursesw5-dev
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_library(Display Display.cpp Display.h constants.h xtermColors.h)
add_library(Keyboard Keyboard.cpp Keyboard.h)
target_link_libraries(Display ${CURSES_LIBRARIES})
target_link_libraries(Keyboard ${CURSES_LIBRARIES})


add_executable(DisplayTest main.cpp Display Keyboard bitmap_image.hpp)
target_link_libraries(DisplayTest ${CURSES_LIBRARIES})


