cmake_minimum_required(VERSION 3.16)
project(GameProject)

set(CMAKE_CXX_STANDARD 17)

#Try sudo apt install libncurses-dev if not installed
#sudo apt-get install libncursesw5-dev
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB DISPLAY ${CMAKE_SOURCE_DIR}/Display/*.*)
file(GLOB EVENTS ${CMAKE_SOURCE_DIR}/Events/*.*)
file(GLOB GAMEDATA ${CMAKE_SOURCE_DIR}/GameData/*.*)
file(GLOB BASIC ${CMAKE_SOURCE_DIR}/Basic/*.*)
file(GLOB BINDER ${CMAKE_SOURCE_DIR}/Basic/Binder/*.*)
file(GLOB NEWEVENTLISTENERINFO ${CMAKE_SOURCE_DIR}/Events/NewEventListenerInfo/*.*)

add_executable(game main.cpp Manager.h Manager.cpp ${BASIC} ${DRAW} ${EVENTS} ${GAMEDATA} ${DISPLAY} ${NEWEVENTLISTENERINFO} ${BINDER})
target_include_directories(game PUBLIC
${CMAKE_SOURCE_DIR}/Basic
${CMAKE_SOURCE_DIR}/Display
${CMAKE_SOURCE_DIR}/Events
${CMAKE_SOURCE_DIR}/GameData
${CMAKE_SOURCE_DIR}/Events/NewEventListenerInfo
${CMAKE_SOURCE_DIR}/Basic/Binder)
target_link_libraries(game ${CURSES_LIBRARIES})