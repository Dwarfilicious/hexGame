find_package(glfw3 REQUIRED)

set(SOURCES
    OpenGLRenderer.cpp
)

add_library(renderer ${SOURCES})

target_include_directories(renderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(renderer
    camera
    components
    entities
    world
    glfw3
)
