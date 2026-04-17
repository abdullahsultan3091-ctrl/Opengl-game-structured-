find_package(OpenGL REQUIRED)

add_executable(RainbowBreakout main.cpp)

target_link_libraries(RainbowBreakout PRIVATE
    game_object
    collision
    shader
    renderer
    glfw
    glad
    OpenGL::GL
)