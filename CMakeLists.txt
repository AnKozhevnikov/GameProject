cmake_minimum_required(VERSION 3.8)
project(GameProject)

set(CMAKE_CXX_STANDARD 17)

file(GLOB DISPLAY ${CMAKE_SOURCE_DIR}/Display/*.*)
file(GLOB EVENTS ${CMAKE_SOURCE_DIR}/Events/*.*)
file(GLOB GAMEDATA ${CMAKE_SOURCE_DIR}/GameData/*.*)
file(GLOB BASIC ${CMAKE_SOURCE_DIR}/Basic/*.*)

add_executable(game main.cpp Monitor.h Monitor.cpp ${BASIC} ${DRAW} ${EVENTS} ${GAMEDATA})
target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/Basic ${CMAKE_SOURCE_DIR}/Draw ${CMAKE_SOURCE_DIR}/Events ${CMAKE_SOURCE_DIR}/GameData)