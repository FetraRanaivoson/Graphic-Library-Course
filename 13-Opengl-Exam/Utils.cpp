//
// Created by Administrator on 8/13/2021.
//
#include"Utils.h"


void Utils::drawAxis(float taille) {
    glPushMatrix();
    glScaled(taille, taille, taille);
    glLineWidth(2);
    glBegin(GL_LINES);
    //axe des x
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    //axe des y
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    //axe des x
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
    glLineWidth(1);
    glPopMatrix();
}
void Utils::drawQuads(float height, float lenght, float red, float green, float blue) {
    glPushMatrix();
    glScaled(lenght, height, 1);
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glVertex2f(0, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glVertex2f(0, 0);
    glEnd();
    glEnd();
    glPopMatrix();
}
void Utils::drawQuadsHollow(float height, float lenght, float red, float green, float blue) {
    glPushMatrix();
    glScaled(lenght, height, 1);
    glBegin(GL_LINE_LOOP);
    glColor3f(red, green, blue);
    glVertex2f(0, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glVertex2f(0, 0);
    glEnd();
    glPopMatrix();
}
void Utils::drawCube(float tailleX, float tailleY, float tailleZ) {
    glPushMatrix();
    glScalef(tailleX, tailleY, tailleZ);
    glBegin(GL_QUADS);
    //face du bas
    glColor3f(0.1, 0.1, 0.1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    //face du gauche
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    //face du gauche
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);

    //face du droite
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    //face du droite
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

    //face du droite
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glEnd();
    glPopMatrix();
}
void Utils::drawCube(float tailleX, float tailleY, float tailleZ, float red, float green, float blue) {
    glPushMatrix();
    glScalef(tailleX, tailleY, tailleZ);
    glBegin(GL_QUADS);
    //face du bas
    glColor3f(red, green, blue);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    //face du gauche
    glColor3f(red, green, blue);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    //face du gauche
    glColor3f(red, green, blue);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);

    //face du droite
    glColor3f(red, green, blue);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    //face du droite
    glColor3f(red, green, blue);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

    //face du droite
    glColor3f(red, green, blue);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glEnd();
    glPopMatrix();
}
GLuint Utils::loadTexture(std::string path) {
    GLuint idTexture = 0;
    SDL_Surface *surfaceTemp1 = IMG_Load(path.c_str());
    if (surfaceTemp1 == nullptr) {
        SDL_Log("file not load");
        exit(404);
    }
    SDL_Surface *surfaceTemp2 = flipSurface(surfaceTemp1);
    glGenTextures(1, &idTexture);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    int Mode = GL_RGB;
    if (surfaceTemp2->format->BytesPerPixel == 4) {
        Mode = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, Mode, surfaceTemp2->w, surfaceTemp2->h, 0, Mode, GL_UNSIGNED_BYTE,
                 surfaceTemp2->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(surfaceTemp1);
    SDL_FreeSurface(surfaceTemp2);
    glBindTexture(GL_TEXTURE_2D, 0);
    return idTexture;
}
SDL_Surface *Utils::flipSurface(SDL_Surface *surface) {
    int current_line, pitch;
    SDL_Surface *fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                                       surface->w, surface->h,
                                                       surface->format->BitsPerPixel,
                                                       surface->format->Rmask,
                                                       surface->format->Gmask,
                                                       surface->format->Bmask,
                                                       surface->format->Amask);
    SDL_LockSurface(surface);
    SDL_LockSurface(fliped_surface);
    pitch = surface->pitch;
    for (current_line = 0; current_line < surface->h; current_line++) {
        memcpy(&((unsigned char *) fliped_surface->pixels)[current_line * pitch],
               &((unsigned char *) surface->pixels)[(surface->h - 1 -
                                                     current_line) * pitch],
               pitch);
    }
    SDL_UnlockSurface(fliped_surface);
    SDL_UnlockSurface(surface);
    return fliped_surface;
}
void Utils::drawCube(float tailleX, float tailleY, float tailleZ, GLuint idTexture) {
    glPushMatrix();
    glScalef(tailleX, tailleY, tailleZ);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    glBegin(GL_QUADS);
    //face du bas
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -1);

    //face du devant
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, 1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, 1);

    //face du gauche
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(-1, 1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, 1);

    //face du derriere
    glTexCoord2f(0, 0);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, -1);

    //face du droite
    glTexCoord2f(0, 0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(1, -1, -1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(1, 1, 1);

    //face du haut
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, 1);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, 1);
    glTexCoord2f(1, 1);
    glVertex3f(1, 1, -1);
    glTexCoord2f(0, 1);
    glVertex3f(-1, 1, -1);
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Utils::drawSkybox(float tailleX, float tailleY, float tailleZ, GLuint idTexture) {
    float v1_3 = 1.0 / 3.0;
    float v1_4 = 1.0 / 4.0;
    float v1_2 = 1.0 / 2.0;
    float v2_3 = 2.0 / 3.0;
    float v3_4 = 3.0 / 4.0;
    float v0 = 0.0;
    float v1 = 1.0;
    glPushMatrix();
    glScalef(tailleX, tailleY, tailleZ);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    glBegin(GL_QUADS);

    //face avant
    glColor3f(1, 1, 1);
    glTexCoord2f(v1_4, v1_3);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(v1_2, v1_3);
    glVertex3f(1, -1, 1);
    glTexCoord2f(v1_2, v2_3);
    glVertex3f(1, 1, 1);
    glTexCoord2f(v1_4, v2_3);
    glVertex3f(-1, 1, 1);

    //face du gauche
    glColor3f(1, 1, 1);
    glTexCoord2f(v1_4, v1_3);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(v0, v1_3);
    glVertex3f(-1, -1, -1);
    glTexCoord2f(0, v2_3);
    glVertex3f(-1, 1, -1);
    glTexCoord2f(v1_4, v2_3);
    glVertex3f(-1, 1, 1);

    //face du droite
    glColor3f(1, 1, 1);
    glTexCoord2f(v1_2, v1_3);
    glVertex3f(1, -1, 1);
    glTexCoord2f(v3_4, v1_3);
    glVertex3f(1, -1, -1);
    glTexCoord2f(v3_4, v2_3);
    glVertex3f(1, 1, -1);
    glTexCoord2f(v1_2, v2_3);
    glVertex3f(1, 1, 1);

    //face du arriere
    glColor3f(1, 1, 1);
    glTexCoord2f(v1, v1_3);
    glVertex3f(1, -1, -1);
    glTexCoord2f(v1, v2_3);
    glVertex3f(1, 1, -1);
    glTexCoord2f(v3_4, v2_3);
    glVertex3f(-1, 1, -1);
    glTexCoord2f(v3_4, v1_3);
    glVertex3f(-1, -1, -1);

    //face du haut
    glColor3f(1, 1, 1);
    glTexCoord2f(v1_2, v2_3);
    glVertex3f(1, 1, 1);
    glTexCoord2f(v1_2, v1);
    glVertex3f(1, 1, -1);
    glTexCoord2f(v1_4, v1);
    glVertex3f(-1, 1, -1);
    glTexCoord2f(v1_4, v2_3);
    glVertex3f(-1, 1, 1);

    //face du bas
    glColor3f(1, 1, 1);
    glTexCoord2f(v1_4, v0);
    glVertex3f(-1, -1, 1);
    glTexCoord2f(v1_2, v0);
    glVertex3f(1, -1, 1);
    glTexCoord2f(v1_2, v1_3);
    glVertex3f(1, -1, -1);
    glTexCoord2f(v1_4, v1_3);
    glVertex3f(-1, -1, -1);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, NULL);
    glPopMatrix();
}

void Utils::drawCube(float translateX, float translateY, float translateZ, float rotateX, float rotateY, float rotateZ,
                     float scaleX, float scaleY, float scaleZ) {
        glPushMatrix();
        glTranslatef(translateX, translateY, translateZ);
        glRotatef(rotateY, 0, 1, 0);
        drawAxis(2);

        glScalef(scaleX, scaleY, scaleZ);

        //face du bas
        glBegin(GL_QUADS);
        glColor3f(.01, .01, 0.1);
        glVertex3f(-1, -1, 1);
        glVertex3f(1, -1, 1);
        glVertex3f(1, -1, -1);
        glVertex3f(-1, -1, -1);

        //face du gauche
        glColor3f(.1, .1, .1);
        glVertex3f(-1, -1, 1);
        glVertex3f(1, -1, 1);
        glVertex3f(1, 1, 1);
        glVertex3f(-1, 1, 1);

        //face du gauche
        glColor3f(1, 0, 0);
        glVertex3f(-1, -1, 1);
        glVertex3f(-1, -1, -1);
        glVertex3f(-1, 1, -1);
        glVertex3f(-1, 1, 1);

        //face du droite
        glColor3f(0, 1, 0);
        glVertex3f(-1, -1, -1);
        glVertex3f(1, -1, -1);
        glVertex3f(1, 1, -1);
        glVertex3f(-1, 1, -1);

        //    //face du droite
        glColor3f(.15, .15, 0.15);
        glVertex3f(1, -1, 1);
        glVertex3f(1, -1, -1);
        glVertex3f(1, 1, -1);
        glVertex3f(1, 1, 1);

        //    //face du droite
        glColor3f(.5, .5, 0.5);
        glVertex3f(-1, 1, 1);
        glVertex3f(1, 1, 1);
        glVertex3f(1, 1, -1);
        glVertex3f(-1, 1, -1);
        glEnd();

        glPopMatrix();

}
