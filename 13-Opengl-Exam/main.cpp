#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Box.h"
#include "Utils.h"
#include "SkyBox.h"
#include "Platform.h"
#include "BoxSpawner.h"
#include "time.h"

#include <iostream>

void getState(Box *box, Uint32 button, const Uint8 *state);

int main(int argc, char **args) {

    srand(time(NULL));

    SDL_Window *win;
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    win = SDL_CreateWindow("Animated player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
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


    //Initialize objects
    Platform *bottomPlatform = new Platform(0, 0, 0, 0, 0, 0, 50, 1, 50);
    Platform *ceilingPlatform = new Platform(0, 55, 0, 0, 0, 0, 50, 1, 50);
    Box *player = new Box(2, 3, 0, 0, 0, 0, 3, 3, 3);
    BoxSpawner *boxSpawner = new BoxSpawner(ceilingPlatform->getPosX(), ceilingPlatform->getPosY(),
                                            ceilingPlatform->getPosZ());
    SkyBox *skyBox = new SkyBox();


    Uint32 button;
    const Uint8 *state;
    SDL_Event event;
    Uint32 time = 0;
    Uint32 lastSpawn = 0;
    int timeToSpawn = rand() % 5000 + 1000;  //Btw 1000ms and 5000ms

    std::vector<Box *> allBoxes;

    int mouseClickX, mouseClickY;
    while (isRunning) {
        time = SDL_GetTicks();


        glLoadIdentity();
        gluLookAt(player->getPosX() + 50, player->getPosY() + 5, player->getPosZ() + 50,
                  player->getPosX(), player->getPosY(), player->getPosZ(),
                  0, 1, 0);

        //Clean window
        glClearColor(0.0f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //Handle events
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        state = SDL_GetKeyboardState(NULL);
        SDL_PumpEvents();
        button = SDL_GetMouseState(&mouseClickX, &mouseClickY);
        getState(player, button, state);


        //Collisions
        allBoxes = boxSpawner->getBoxes();
        for (Box *box : allBoxes) {
            if (player->collide(box)) {
                std::cout << "Collided!!" << std::endl;
            }
        }


        //Draw objects
        bottomPlatform->draw();
        ceilingPlatform->draw();
        player->draw();
        skyBox->draw();
        

        //Spawn boxes
        if (time - lastSpawn > timeToSpawn) {
            int t = time - lastSpawn;
            boxSpawner->randomizeBoxPosition();
            lastSpawn = time;
        }
        boxSpawner->spawnBoxes();


        Utils::drawAxis(1);
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

void getState(Box *box, Uint32 button, const Uint8 *state) {
    if ((button & SDL_BUTTON_LMASK) != 0) {
        box->move(Direction::FORWARD);
    }
    if ((button & SDL_BUTTON_RMASK) != 0) {
        box->move(Direction::BACKWARD);
    }
    if (state[SDL_SCANCODE_UP])
        box->move(Direction::UP);
    if (state[SDL_SCANCODE_DOWN])
        box->move(Direction::DOWN);
    if (state[SDL_SCANCODE_LEFT])
        box->move(Direction::ROTATE_LEFT);
    if (state[SDL_SCANCODE_RIGHT])
        box->move(Direction::ROTATE_RIGHT);
}

