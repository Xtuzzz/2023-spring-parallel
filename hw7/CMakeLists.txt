cmake_minimum_required(VERSION 3.13)
project(hw7)

set(CMAKE_CXX_STANDARD 23)

add_definitions(-w)

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
IF (APPLE)
    include_directories(
            ${BLAS_LIBRARIES}/../vecLib.framework/Headers
    )
ELSEIF (UNIX)
    include_directories(
            /usr/include/x86_64-linux-gnu/
    )
ENDIF ()



include_directories(
        ${PROJECT_SOURCE_DIR}/src/
)


link_libraries(${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_executable(hw7 src/main.cpp src/Input.cpp src/Input.h src/Timer.cpp)
