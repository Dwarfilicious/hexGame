add_library(world
    World.cpp
    TileTypes.cpp
    Tile.cpp
)

target_include_directories(world PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/world
)

target_link_libraries(world PUBLIC
    math
    ecs
)
