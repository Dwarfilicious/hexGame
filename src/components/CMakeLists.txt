set(SOURCES
    Transform.cpp
    Mesh.cpp
    Vertex.cpp
)

add_library(components ${SOURCES})

target_include_directories(components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(components PUBLIC math)
