#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/GL.h>
#include <gl/GLU.h>


#include "Utilities/Transform.h"
#include "Enemy.h"

#include "Utilities/UtilsFetra.h"



int main(int argc, char **args) {
    SDL_Window *win;
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Follower", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                           SDL_WINDOW_OPENGL);


    //Opengl version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    //Create context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);


    //Call projection matrix
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    GLUquadric *params = gluNewQuadric();

    //Initialize projection matrix to 0
    glLoadIdentity();


    //Modify projection matrix if needed
    gluPerspective(70, (double) 800 / 600, 1, 1000);
    glMatrixMode(GL_MODELVIEW);


    //A FLOOR
    Transform *floor = new Transform(0, 0, 0, 0, 0, 0, 50, .001, 50);

    //AN ENEMY
    Enemy *enemy = new Enemy(params);

    //A player position example
    Transform *player = new Transform(5, 1, -15, 0, 0, 0, 1, 1, 1);


    SDL_Event event;
    const Uint8 *state = nullptr;

    while (isRunning) {
        glLoadIdentity();
        gluLookAt(0, 10, 20, 0, 0, 0, 0, 1, 0);


        //Clean window
        glClearColor(0.0f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //Event handling
        SDL_PollEvent(&event);
        state = SDL_GetKeyboardState(NULL);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }



        state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_UP])
            player->incrementPosX(.1);
        if (state[SDL_SCANCODE_DOWN])
            player->incrementPosX(-.1);
        if (state[SDL_SCANCODE_LEFT])
            player->setRotateX(player->getRotateX() + 1);
        if (state[SDL_SCANCODE_RIGHT])
            player->setRotateX(player->getRotateX() - 1);


        //A Floor
        drawCube(floor->getPosX(), floor->getPosY(), floor->getPosZ(),
                 0, 0, 0,
                 floor->getScaleX(), floor->getScaleY(), floor->getScaleZ());


        //A Player example
        drawCube(player->getPosX(), player->getPosY(), player->getPosZ(),
                 0, player->getRotateX(), 0,
                 player->getScaleX(), player->getScaleY(), player->getScaleZ());


        //An Enemy tracking the player
        enemy->draw();
        enemy->trackPlayer(player->getPosX(), player->getPosY(), player->getPosZ());


        //drawAxis(2);


        //Update screen
        glFlush();
        SDL_GL_SwapWindow(win);


        //Pause image
        SDL_Delay(1);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
                        
