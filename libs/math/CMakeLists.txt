add_library(math STATIC
    src/math.cpp
    src/Color.cpp
    src/Vector3.cpp
    src/Matrix4.cpp
    src/Quaternion.cpp
)

target_include_directories(math PUBLIC
    include
)
