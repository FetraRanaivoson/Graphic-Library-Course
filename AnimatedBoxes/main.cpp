#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/GL.h>
#include <gl/GLU.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "Utils.h"
#include "Transform.h"


int main() {
    SDL_Window *win;
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("opengl3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
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
    gluPerspective(70, (double)800 / 600, 1, 1000);
    glMatrixMode(GL_MODELVIEW);

    //Floor
    auto* floor = new Transform(0,0,0,0,0,0,4,.1,4);
    auto* leftWall = new Transform(-4, 2, 0,0,0,0, .1, 2, 4);
    auto* farWall = new Transform(0,2,-4,0,0,0,4,2,.5);
    auto* box1 = new Transform(2, .55, 0,0,0,0, .75, .5, .75);
    auto* box2 = new Transform(3,.55,2,0,0,0,.25,.5,.25);
    float box1VelocityX = .01;
    float box2VelocityX = .005;

    const Uint8 *state;
    SDL_Event event;

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


        //Update box1
        box1->incrementPosX(-box1VelocityX);
        if (box1->getPosX() <= leftWall->getPosX() + leftWall->getScaleX() / 2 + box1->getScaleX() 
            || box1->getPosX() >= -leftWall->getPosX() - leftWall->getScaleX() / 2 - box1->getScaleX() ) {
            box1VelocityX *= -1;
        }

        //Update box2
        box2->incrementPosX(-box2VelocityX);
        if (box2->getPosX() <= leftWall->getPosX() + leftWall->getScaleX() / 2 + box2->getScaleX()
        || box2->getPosX() >= -leftWall->getPosX() - leftWall->getScaleX() / 2 - box2->getScaleX()) {
            box2VelocityX *= -1;
        }

        //Floor: push(beg), pop inside (end)
        drawCube(floor->getPosX(), floor->getPosY(), floor->getPosZ(),
                 floor->getScaleX(), floor->getScaleY(), floor->getScaleZ());


        //LeftWall
        drawCube(leftWall->getPosX(), leftWall->getPosY(), leftWall->getPosZ(),
                 leftWall->getScaleX(), leftWall->getScaleY(), leftWall->getScaleZ());

        //FarWall
        drawCube(farWall->getPosX(), farWall->getPosY(), farWall->getPosZ(),
                 farWall->getScaleX(), farWall->getScaleY(), farWall->getScaleZ());

        //Box1
        drawCube(box1->getPosX(), box1->getPosY(), box1->getPosZ(),
                 box1->getScaleX(), box1->getScaleY(), box1->getScaleZ());


        //Box2
        drawCube(box2->getPosX(), box2->getPosY(), box2->getPosZ(),
                 box2->getScaleX(), box2->getScaleY(), box2->getScaleZ());



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

