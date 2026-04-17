add_library(renderer
    src/renderer.cpp
)

target_include_directories(renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(renderer PUBLIC shader game_object glad glm)