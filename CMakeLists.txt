cmake_minimum_required(VERSION 3.16)
project(RainbowBreakout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
    ${CMAKE_SOURCE_DIR}/libs/external_libs
)

add_subdirectory(libs)
add_subdirectory(apps)