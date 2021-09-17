#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Transform.h"
#include "Utils.h"
#include "levelObjects/LevelManager.h"

void drawAxis();

std::vector<Level *> getLevel(int columnCount, int rowCount, LevelManager *levelManager);

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

    auto* floor = new Transform(0,0,0,0,0,0,4,.1,4);

    Uint32 button;
    const Uint8 *state;
    SDL_Event event;

    int x, y;


    int columnCount = 40;
    int rowCount = 20;
    LevelManager *levelManager = new LevelManager();
    std::vector<Level *> retrievedLevel = getLevel(columnCount, rowCount, levelManager);


    float vueRotateX = -5;
    float vueRotateZ = -10;

    while (isRunning) {

        glLoadIdentity();
        gluLookAt(vueRotateX, 20, vueRotateZ, 0, 10, 0, 0, 1, 0);


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
            vueRotateX += .1;
            vueRotateZ += .1;
        }
        if ((button & SDL_BUTTON_RMASK) != 0) {
            vueRotateX -= .1;
            vueRotateZ -= .1;
        }


        drawCube(40, .1, 40);

        for (int row = 0; row < rowCount; row++) {
            for (int col = 0; col < columnCount; col++) {
                int value = retrievedLevel[row]->getNumber(col);
                if (value > 0) {
                    glPushMatrix();
                    glTranslatef( col, value, row);
                    drawCube(.5, value, .5);
                    glPopMatrix();
                }
            }
        }



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

std::vector<Level *> getLevel(int columnCount, int rowCount, LevelManager *levelManager) {
    // ACTIVATE THIS TO APPEND A SET OF RANDOM BINARY NUMBER (col x row) TO FILE
    //levelManager->saveRandomNumbers(columnCount, rowCount);

    std::vector<Level *> retrievedNumbers;
    // ACTIVATE THIS TO LOAD A SET OF BINARY NUMBER FROM FILE
    levelManager->loadRandomNumbers(columnCount, retrievedNumbers);

    // VERIFY IF DATA EXISTS ON THE FILE
    if (!retrievedNumbers.empty()) {
        for (Level *retrieved : retrievedNumbers) {
            retrieved->print();
        }
    } else std::cout << "No data to retrieve" << std::endl;
    return retrievedNumbers;
}

