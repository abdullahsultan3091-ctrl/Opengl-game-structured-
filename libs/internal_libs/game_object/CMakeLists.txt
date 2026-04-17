add_library(game_object
    src/game_object.cpp
)

target_include_directories(game_object PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(game_object PUBLIC glm)