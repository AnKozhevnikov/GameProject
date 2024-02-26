cmake_minimum_required(VERSION 3.8)
project(GameProject)

set(CMAKE_CXX_STANDARD 17)

file(GLOB DRAW ${CMAKE_SOURCE_DIR}/Draw/*.*)
file(GLOB EVENTS ${CMAKE_SOURCE_DIR}/Events/*.*)
file(GLOB GAMEDATA ${CMAKE_SOURCE_DIR}/GameData/*.*)

add_executable(game main.cpp Game.h Game.cpp Monitor.h Monitor.cpp ${DRAW} ${EVENTS} ${GAMEDATA})
target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/Draw ${CMAKE_SOURCE_DIR}/Events ${CMAKE_SOURCE_DIR}/GameData)