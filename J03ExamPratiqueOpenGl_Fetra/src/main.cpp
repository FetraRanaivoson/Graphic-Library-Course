#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Transform.h"
#include "Utils.h"
#include "SkyBox.h"
#include "Platform.h"
#include <SDL2/SDL_image.h>


int main(int argc, char **args) {
    SDL_Window *win;
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    win = SDL_CreateWindow("Animated box", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                           SDL_WINDOW_OPENGL);


    //creation du context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);

    //appelle la matrice de projection
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);

    //initialise la matrice de projection à 0
    glLoadIdentity();

    //modifie la matrice de projection pour avoir la perspective voulue
    gluPerspective(70, (double) 800 / 600, 1, 1000);
    glMatrixMode(GL_MODELVIEW);

    ///////////////////
    auto* bottomFloor = new Transform(0, 0, 0, 0, 0, 0, 50, 1, 50);
    auto* ceiling = new Transform(0, 75, 0, 0, 0, 0, 50, 1, 50);
    Platform* bottomPlatform = new Platform(0, 0, 0, 0, 0, 0, 50, 1, 50);
    Platform* ceilingPlatform = new Platform(0, 75, 0, 0, 0, 0, 50, 1, 50);
    ///////////////////




    auto* boxTransform = new Transform(2, 3, 0, 0, 0, 0,3 , 3, 3);
    float boxVelocity = .1;

    SkyBox* skyBox = new SkyBox();

    Uint32 button;
    const Uint8 *state;
    SDL_Event event;

    int x, y;

    while (isRunning) {

        glLoadIdentity();
        gluLookAt(boxTransform->getPosX() + 10, boxTransform->getPosY(), boxTransform->getPosZ() + 10,
                  boxTransform->getPosX(), boxTransform->getPosY(), boxTransform->getPosZ(),
                  0, 1, 0);


        //Nettoyer la fenêtre
        glClearColor(0.0f, 0.f, 0.f,
                     1.f); //permet d'expliquer avec quelle couleur on va remplir la memoire des couleurs
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }


        state = SDL_GetKeyboardState(NULL);

        SDL_PumpEvents();
        button = SDL_GetMouseState(&x, &y);

        if ((button & SDL_BUTTON_LMASK) != 0) {
            boxTransform->incrementPosX(boxVelocity);
        }
        if ((button & SDL_BUTTON_RMASK) != 0) {
            boxTransform->incrementPosX(-boxVelocity);
        }

        if (state[SDL_SCANCODE_UP])
            boxTransform->incrementPosY(boxVelocity);
        if (state[SDL_SCANCODE_DOWN])
            boxTransform->incrementPosY(-boxVelocity);

        if (state[SDL_SCANCODE_LEFT])
            boxTransform->setRotateX(boxTransform->getRotateX() + 1);
        if (state[SDL_SCANCODE_RIGHT])
            boxTransform->setRotateX(boxTransform->getRotateX() - 1);


        //Floor
        Utils::drawCube(bottomFloor->getPosX(), bottomFloor->getPosY(), bottomFloor->getPosZ(),
                        0, 0, 0,
                        bottomFloor->getScaleX(), bottomFloor->getScaleY(), bottomFloor->getScaleZ());

        //Ceiling
        Utils::drawCube(ceiling->getPosX(), ceiling->getPosY(), ceiling->getPosZ(),
                        0, 0, 0,
                        ceiling->getScaleX(), ceiling->getScaleY(), ceiling->getScaleZ());

        //Box
        Utils::drawCube(boxTransform->getPosX(), boxTransform->getPosY(), boxTransform->getPosZ(),
                        0,boxTransform->getRotateX(),0,
                        boxTransform->getScaleX(), boxTransform->getScaleY(), boxTransform->getScaleZ());

        //SkyBox
        skyBox->draw();





        Utils::drawAxis(1);
        //mise a jour de l'écran
        glFlush();
        SDL_GL_SwapWindow(win);

        //pause dans l'image
        SDL_Delay(1);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

