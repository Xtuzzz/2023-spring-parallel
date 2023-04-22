cmake_minimum_required(VERSION 3.13)
project(hw7)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-w)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
IF (APPLE)
ELSE()
    include_directories(
            /usr/include/
    )
    link_libraries(/usr/lib/x86_64-linux-gnu/liblapacke.so)
ENDIF ()

include_directories(
        ${PROJECT_SOURCE_DIR}/src/
)


link_libraries(${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_executable(hw7 src/main.cpp src/Input.cpp src/Timer.cpp)
