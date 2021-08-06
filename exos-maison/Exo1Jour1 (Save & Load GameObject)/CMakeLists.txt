cmake_minimum_required(VERSION 3.20)
project(Exo1Jour1)

set(CMAKE_CXX_STANDARD 20)

file(
        COPY
        assets
        DESTINATION
        ${CMAKE_BINARY_DIR}
)

add_executable(Exo1Jour1 main.cpp GameObject.cpp GameObject.h)
