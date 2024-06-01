set(SOURCES
    Tile.cpp
    Entity.cpp
    TileTypes.cpp
)

add_library(entities ${SOURCES})

target_include_directories(entities PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(entities PUBLIC math components)
