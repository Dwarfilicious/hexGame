add_library(ecs STATIC
    src/Camera.cpp
    src/Entity.cpp
    src/EntityContainer.cpp
    src/Mesh.cpp
    src/RayCast.cpp
    src/Transform.cpp
    src/Vertex.cpp
)

target_include_directories(ecs PUBLIC
    include
)

target_link_libraries(ecs PUBLIC
    math
)
