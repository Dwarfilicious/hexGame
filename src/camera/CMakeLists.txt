set(SOURCES
    Camera.cpp
)

add_library(camera ${SOURCES})

target_include_directories(camera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(camera PUBLIC math components)
