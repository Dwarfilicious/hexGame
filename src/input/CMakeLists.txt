find_package(glfw3 REQUIRED)

set(SOURCES
    InputHandler.cpp
    InputResponder.cpp
)

add_library(input ${SOURCES})

target_include_directories(input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(input PUBLIC math camera components glfw3)
