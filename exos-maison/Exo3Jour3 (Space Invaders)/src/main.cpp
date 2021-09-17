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

    Uint32 format;
    //SDL_Texture *bgSmall = IMG_LoadTexture(renderer, "./assets/bgSmall.png");
    SDL_Texture *bgSmall = IMG_LoadTexture(renderer, "./assets/bg2.jpg");
    if (!bgSmall)
        SDL_Log("pb");

    int wI, hI;
    SDL_QueryTexture(bgSmall, &format, NULL, &wI, &hI);

    int wS, hS;
    SDL_Texture *bigBg = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, wI, 3 * hI);
    wS = wI;
    hS = hI / 3;


    SDL_Rect position = {0, 0, wI, hI};
    SDL_SetRenderTarget(renderer, bigBg); // cibler la texture ou je vais copier
    SDL_RenderCopy(renderer, bgSmall, NULL, &position);
    position.y += hI;
    //SDL_RenderCopyEx(renderer, bgSmall,NULL, &position,0, NULL, SDL_FLIP_VERTICAL);
    //position.y +=hI;
    SDL_RenderCopy(renderer, bgSmall, NULL, &position);
    SDL_SetRenderTarget(renderer, NULL); // je fais des copie sur l ecran
    position.y = position.h;


    Uint32 currentTime = 0;
    Uint32 lastUpdate = 0;
    int bgDeltaTime = 20;


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

    bool noEnemyLeft = false;

    while (isRunning) {
        currentTime = SDL_GetTicks();

        //Clean window
        SDL_SetRenderDrawColor(renderer, 0, 51, 102, 255);
        SDL_RenderClear(renderer);


        if (noEnemyLeft) {
            std::vector<Level *> retrievedLevel = getLevel(columnCount, rowCount, levelManager);
            positionEnemies(columnCount, rowCount, retrievedLevel, enemySpacingX, enemySpacingY, enemies);
            noEnemyLeft = false;
        }


        //Event handling
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }


        if (currentTime - lastUpdate > bgDeltaTime) {
            position.y -= 1;
            lastUpdate = currentTime;
            if (position.y <= 0)
                position.y = position.h;

        }

        SDL_RenderCopy(renderer, bigBg, &position, NULL);


        //Update game objects
        player->update(renderer,SDL_GetTicks());
        for (Enemy *e : enemies) {
            e->update(renderer, SDL_GetTicks());
        }


        //Draw game objects
        player->display(renderer);
        for (Enemy *e: enemies) {
            e->display(renderer);
        }

        for (int i=0; i < enemies.size(); i++) {
            if (enemies[i]->isTouchedBy(player->getAmmo())){
                enemies.erase(enemies.cbegin() + i);
            }
        }

        if (enemies.empty()) {
            noEnemyLeft = true;
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
    SDL_DestroyTexture(bgSmall);
    SDL_DestroyTexture(bigBg);
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
                        