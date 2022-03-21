//
// Created by Administrator on 8/17/2021.
//

#ifndef ENEMY_H
#define ENEMY_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/GL.h>
#include <gl/GLU.h>


#include <stdlib.h>
#include <time.h>

#include "Utilities/Point.h"

#define _USE_MATH_DEFINES
#include <cmath>

class Enemy {

private:
    GLuint enemyID;

    float enemyPosX = 0;
    float enemyPosY = 0;
    float enemyPosZ = 0;
    float velocity = 0.01;

    float rotationAngle = 0;

    float currentX = 0;
    float lastX = 0;
    float currentZ = 0;
    float lastZ = 0;

public:
    Enemy(GLUquadric *params);
    void draw() const;
    void trackPlayer(float x, float y, float z);
    virtual ~Enemy();

    float deltaX() const;
    float deltaZ() const;
};
#endif 
