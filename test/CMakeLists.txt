find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(renderTest renderTest.cpp)

target_link_libraries(renderTest
    camera
    components
    entities
    input
    math
    renderer
    world
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${GLEW_LIBRARY}
)
