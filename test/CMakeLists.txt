find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(renderTest renderTest.cpp)

target_link_libraries(renderTest
    camera
    input
    renderer
    world
    globalVars
)
