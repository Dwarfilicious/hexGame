add_executable(renderTest renderTest.cpp)

target_link_libraries(renderTest
    camera
    input
    renderer
    world
    globalVars
)
