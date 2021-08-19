//
// Created by Administrator on 8/19/2021.
//

#ifndef DEMOFIRSTSDL_PLATFORM_H
#define DEMOFIRSTSDL_PLATFORM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Platform {
private:
    GLuint idSkyBox;
    float px, py, pz, rx, ry, rz, sx, sy,sz;

public:

    Platform();
    Platform(float px, float py, float pz, float rx, float ry, float rz,
             float sx, float sy, float sz);

};


#endif //DEMOFIRSTSDL_PLATFORM_H
