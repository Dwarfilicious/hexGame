set(SOURCES
    World.cpp
)

add_library(world ${SOURCES})

target_include_directories(world PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(world PUBLIC entities)
