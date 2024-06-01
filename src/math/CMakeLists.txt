set(SOURCES
    Vector3.cpp
    Quaternion.cpp
    Matrix4.cpp
    Color.cpp
    math.cpp
)

add_library(math ${SOURCES})

target_include_directories(math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
