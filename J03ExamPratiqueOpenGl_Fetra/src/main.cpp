#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Transform.h"
#include "Utils.h"
void drawAxis();

int main(int argc, char **args) {
    SDL_Window *win;
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Animated box", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                           SDL_WINDOW_OPENGL);



    //creation du context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);

    //appelle la matrice de projection
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);

    //initialise la matrice de projection à 0
    glLoadIdentity();

    //modifie la matrice de projection pour avoir la perspective voulue
    gluPerspective(70, (double) 800 / 600, 1, 1000);
    glMatrixMode(GL_MODELVIEW);

    //Floor
    auto* floor = new Transform(0,0,0,0,0,0,4,.1,4);
    auto* leftWall = new Transform(-4, 2, 0,0,0,0, .1, 2, 4);
    auto* farWall = new Transform(0,2,-4,0,0,0,4,2,.5);
    auto* box1 = new Transform(2, .55, 0,0,0,0, .75, .5, .75);

    float box1VelocityPositionX = .01;
    float box1VelocityRotationY = 0;
    //float box2VelocityX = .005;

    Uint32 button;
    const Uint8 *state;
    SDL_Event event;

    int x, y;

    while (isRunning) {

        glLoadIdentity();
        gluLookAt(3, 5, 7, 0, 0, 0, 0, 1, 0);


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
            box1->setRotateX(box1->getRotateX() + 1);
        }
        if ((button & SDL_BUTTON_RMASK) != 0) {
            box1->setRotateX(box1->getRotateX() - 1);
        }

        if (state[SDL_SCANCODE_UP])
            box1->incrementPosX(box1VelocityPositionX);
        if (state[SDL_SCANCODE_DOWN])
            box1->incrementPosX(-box1VelocityPositionX);
        if (state[SDL_SCANCODE_LEFT])
            box1->setRotateX(box1->getRotateX() + 1);
        if (state[SDL_SCANCODE_RIGHT])
            box1->setRotateX(box1->getRotateX() - 1);


        //Floor: push(beg), pop inside (end)
        drawCube(floor->getPosX(), floor->getPosY(), floor->getPosZ(),
                 0,0,0,
                 floor->getScaleX(), floor->getScaleY(), floor->getScaleZ());
        //LeftWall
        drawCube(leftWall->getPosX(), leftWall->getPosY(), leftWall->getPosZ(),
                 0,0,0,
                 leftWall->getScaleX(), leftWall->getScaleY(), leftWall->getScaleZ());
        //FarWall
        drawCube(farWall->getPosX(), farWall->getPosY(), farWall->getPosZ(),
                 0,0,0,
                 farWall->getScaleX(), farWall->getScaleY(), farWall->getScaleZ());
        //Box1
        drawCube(box1->getPosX(), box1->getPosY(), box1->getPosZ(),
                 0,box1->getRotateX(),0,
                 box1->getScaleX(), box1->getScaleY(), box1->getScaleZ());


        drawAxis(1);


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

