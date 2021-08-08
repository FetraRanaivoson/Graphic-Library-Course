#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "iostream"
#include "gameObjects/Player.h"
#include "gameObjects/Enemy.h"
#include "levelObjects/LevelManager.h"

SDL_Window *win;
SDL_Renderer *renderer;
int windowW = 800, windowH = 600;


std::vector<Level *> getLevel(int columnCount, int rowCount, LevelManager *levelManager);

void positionEnemies(int columnCount, int rowCount, const std::vector<Level *> &retrievedLevel, int enemySpacingX,
                     int enemySpacingY, std::vector<Enemy *> &enemies);

int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Event event;


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_CreateWindowAndRenderer(windowW, windowH, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win,
                                &renderer);


    int columnCount = 10;
    int rowCount = 3;
    LevelManager *levelManager = new LevelManager();
    std::vector<Level *> retrievedLevel = getLevel(columnCount, rowCount, levelManager);


    //Setup display
    int enemySpacingX = windowW / columnCount;
    int enemySpacingY = 60;
    SDL_Rect rect;
    rect.w = enemySpacingX;
    rect.h = enemySpacingY;


    //Instantiate objects
    Player *player = new Player(renderer, windowW, windowH, windowW / 2, windowH - 90);
    player->initializeImage(renderer, windowW, windowH);

    std::vector<Enemy *> enemies;
    positionEnemies(columnCount, rowCount, retrievedLevel, enemySpacingX, enemySpacingY, enemies);

    while (isRunning) {

        //Clean window
        SDL_SetRenderDrawColor(renderer, 0, 51, 102, 255);
        SDL_RenderClear(renderer);

        //Event handling
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }


        //Update game objects
        player->update(SDL_GetTicks());
        for (Enemy *e : enemies) {
            e->update(SDL_GetTicks());
        }


        //Draw game objects
        player->display(renderer);
        for (Enemy *e: enemies) {
            e->display(renderer);
        }


        SDL_Delay(1);
        SDL_RenderPresent(renderer);
        //std::cout<<player->getFps()<<std::endl;

        //Update game objects


    }

    player->destroyResources();
    for (Enemy *e: enemies) {
        e->destroyResources();
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

void positionEnemies(int columnCount, int rowCount, const std::vector<Level *> &retrievedLevel, int enemySpacingX,
                     int enemySpacingY, std::vector<Enemy *> &enemies) {
    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < columnCount; col++) {
            if (retrievedLevel[row]->getNumber(col) == 0) {
                //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            } else if (retrievedLevel[row]->getNumber(col) == 1) {
                Enemy *enemy = new Enemy(renderer, windowW, windowH, col * enemySpacingX, row * enemySpacingY);
                enemy->initializeImage(renderer, windowW, windowH);
                enemies.push_back(enemy);

            }
            //rect.x = col * enemySpacingX;
            // rect.y = row * enemySpacingY;
            //SDL_RenderFillRect(renderer, &rect);
        }
    }
}

std::vector<Level *> getLevel(int columnCount, int rowCount, LevelManager *levelManager) {
    // ACTIVATE THIS TO APPEND A SET OF RANDOM BINARY NUMBER (col x row) TO FILE
    //levelManager->saveRandomBinaryNumbers(columnCount, rowCount);

    std::vector<Level *> retrievedNumbers;
    // ACTIVATE THIS TO LOAD A SET OF BINARY NUMBER FROM FILE
    levelManager->loadRandomBinaryNumbers(columnCount, retrievedNumbers);

    // VERIFY IF DATA EXISTS ON THE FILE
    if (!retrievedNumbers.empty()) {
        for (Level *retrieved : retrievedNumbers) {
            retrieved->print();
        }
    } else std::cout << "No data to retrieve" << std::endl;
    return retrievedNumbers;
}
                        