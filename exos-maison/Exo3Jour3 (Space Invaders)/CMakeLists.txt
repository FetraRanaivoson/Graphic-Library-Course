cmake_minimum_required(VERSION 3.17)
set(
        project_name
        spaceInvaders
)
file(
        GLOB_RECURSE
        source_file
        src/*
)
#si besoin de repertoire assets
file(
        COPY
        assets
        DESTINATION
       ${CMAKE_BINARY_DIR}
)
project(${project_name})
set(CMAKE_CXX_STANDARD 17)
add_executable(${project_name} ${source_file} src/gameObjects/Player.cpp src/gameObjects/Player.h src/gameObjects/Enemy.cpp src/gameObjects/Enemy.h src/gameObjects/Spaceship.cpp src/gameObjects/Spaceship.h src/levelObjects/LevelManager.cpp src/levelObjects/LevelManager.h src/levelObjects/Level.cpp src/levelObjects/Level.h)
if (WIN32)
    target_link_libraries(
            ${project_name}
            -lmingw32
            -lSDL2main
            -lSDL2
            -lSDL2_image
    )
endif ()
if(UNIX)
    target_link_libraries(
            ${project_name}
            -lSDL2main
            -lSDL2
            -lSDL2_image
    )
endif()