//
// Created by jlidou on 2021-08-12.
//

#ifndef DEMOFIRSTSDL_UTILS_H
#define DEMOFIRSTSDL_UTILS_H
#include <GL/gl.h>
#include <string>
#include <SDL2/SDL_image.h>
class Utils {
public:
    static void drawAxis(float taille);
    static void drawQuads(float height, float lenght, float red, float green, float blue);
    static void drawQuadsHollow(float height, float lenght, float red, float green, float blue);
    static void drawCube(float tailleX, float tailleY, float tailleZ);
    static void drawCube(float tailleX, float tailleY, float tailleZ, float red, float green, float blue);
    static void drawCube(float tailleX, float tailleY, float tailleZ, GLuint idTexture);



    static void drawCube(float translateX, float translateY, float translateZ, float rotateX, float rotateY, float rotateZ,
                  float scaleX, float scaleY, float scaleZ) ;





    static SDL_Surface * flipSurface(SDL_Surface * surface);
    static GLuint loadTexture(std::string path);
    static void drawSkybox(float tailleX, float tailleY, float tailleZ, GLuint idTexture);
};
#endif //DEMOFIRSTSDL_UTILS_H