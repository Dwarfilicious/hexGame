add_subdirectory(camera)
add_subdirectory(components)
add_subdirectory(entities)
add_subdirectory(input)
add_subdirectory(math)
add_subdirectory(renderer)
add_subdirectory(world)

set(SOURCES
    GlobalVariables.hpp
)

add_library(globalVars ${SOURCES})
target_include_directories(globalVars PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(globalVars PUBLIC renderer input)
