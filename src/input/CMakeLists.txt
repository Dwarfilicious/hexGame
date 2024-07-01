find_package(glfw3 REQUIRED)

add_library(input STATIC
    InputHandler.cpp
    CameraController.cpp
    WorldController.cpp
)

target_include_directories(input PUBLIC
    ${CMAKE_SOURCE_DIR}/include/input
)

target_link_libraries(input PUBLIC
    math
    ecs
    glfw3
    world
)
