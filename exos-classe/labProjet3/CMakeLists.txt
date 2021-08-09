cmake_minimum_required(VERSION 3.17)
set(
        project_name
        labProjet1
)
file(
        GLOB_RECURSE
        source_file
        src/*
)
#si besoin de repertoire assets
#file(
#        COPY
#        assets
#        DESTINATION
#       ${CMAKE_BINARY_DIR}
#)
project(${project_name})
set(CMAKE_CXX_STANDARD 17)
add_executable(${project_name} ${source_file} src/Mur.cpp src/Mur.h src/Player.h)
if (WIN32)
    target_link_libraries(
            ${project_name}
            -lmingw32
            -lSDL2main
            -lSDL2
    )
endif ()
if(UNIX)
    target_link_libraries(
            ${project_name}
            -lSDL2main
            -lSDL2
    )
endif()