add_library(collision
    src/collision.cpp
)

target_include_directories(collision PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(collision PUBLIC game_object glm)