cmake_minimum_required(VERSION 3.22.1)

project(hexGame)

add_subdirectory(src)
add_subdirectory(test)

add_executable(${PROJECT_NAME} game.cpp)
target_link_libraries(${PROJECT_NAME}
    camera
    input
    renderer
    world
    globalVars
)
