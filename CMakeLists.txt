cmake_minimum_required(VERSION 3.20.0)

project(main)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
include_directories(include)
find_package(fmt)
find_package(raylib)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp 
    src/player/player.cpp 
    src/ball/ball.cpp 
    src/ai/ai.cpp 
    src/sound_manager/sound_manager.cpp
    src/score/score.cpp
    )

if (raylib_FOUND)
    message(Raylib found)
else()
    message(Raylib was not found)
endif() 
target_link_libraries(${PROJECT_NAME} fmt::fmt ${raylib_LIBRARIES})


file(COPY ${CMAKE_SOURCE_DIR}/sounds DESTINATION ${CMAKE_BINARY_DIR})
file (COPY ${CMAKE_SOURCE_DIR}/font DESTINATION ${CMAKE_BINARY_DIR})
