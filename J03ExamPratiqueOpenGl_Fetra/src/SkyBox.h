//
// Created by Administrator on 8/19/2021.
//

#ifndef DEMOFIRSTSDL_SKYBOX_H
#define DEMOFIRSTSDL_SKYBOX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Utils.h"

class SkyBox {
private:
    GLuint idSkyBox;

public:
    SkyBox();

    void draw();


};


#endif //DEMOFIRSTSDL_SKYBOX_H
