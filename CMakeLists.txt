cmake_minimum_required(VERSION 3.22.1)
project(hexGame)

include_directories(include)

add_subdirectory(src)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} game.cpp)
target_link_libraries(${PROJECT_NAME}
    camera
    input
    renderer
    world
    ${OPENGL_LIBRARIES}
    glfw3
)

add_custom_target(CopyControlsJSON ALL
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/controls.json $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

add_dependencies(${PROJECT_NAME} CopyControlsJSON)
