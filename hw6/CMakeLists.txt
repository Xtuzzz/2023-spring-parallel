cmake_minimum_required(VERSION 3.25)
project(hw6)

set(CMAKE_CXX_STANDARD 23)

include_directories(${PROJECT_SOURCE_DIR}/include/)

add_executable(hw6 src/main.cpp src/Timer.cpp src/Input.cpp src/Matrix.cpp)
