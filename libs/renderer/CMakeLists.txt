find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(renderer STATIC
    src/OpenGLRenderer.cpp
)

target_include_directories(renderer PUBLIC
    include
)

target_link_libraries(renderer PUBLIC
    math
    ecs
    ${OPENGL_LIBRARIES}
    glfw3
)

