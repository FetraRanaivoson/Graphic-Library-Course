#include <iostream>
#include <SDL2/SDL.h>
#include <fstream>
#include <vector>
#include "FileManager.h"

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;

int main(int argc, char **args) {

    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);
    SDL_Event event;

//    SDL_Rect rect;
//    rect.x = 0;
//    rect.y = 0;
//    rect.w = 50;
//    rect.h = 50;


    int columnCount = 10;
    int rowCount = 7;
    FileManager *fileManager = new FileManager();
    // ACTIVATE THIS TO APPEND A SET OF RANDOM BINARY NUMBER (col x row) TO FILE
    //fileManager->saveRandomBinaryNumbers(columnCount, rowCount);

    std::vector<Numbers *> retrievedNumbers;
    // ACTIVATE THIS TO LOAD A SET OF BINARY NUMBER FROM FILE.
    // CHOOSE DESIRED COLUMN FOR DISPLAY
    fileManager->loadRandomBinaryNumbers(columnCount, retrievedNumbers);

    // VERIFY IF DATA EXISTS ON THE FILE
    if (!retrievedNumbers.empty()) {
        for (Numbers *retrieved : retrievedNumbers) {
            retrieved->print();
        }
    } else std::cout << "No data to retrieve" << std::endl;


    int squareSpacingX = width / columnCount;
    int squareSpacingY = height / rowCount;
    SDL_Rect rect;
//    rect.x = 0 + squareSpacing;
//    rect.y = 0;
    rect.w = squareSpacingX;
    rect.h = squareSpacingY;

    while (isRunning) {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
        SDL_RenderClear(renderer);

        SDL_PollEvent(&event);

        for (int row = 0; row < rowCount; row++) {
            for (int col = 0; col < columnCount; col++) {
                if (retrievedNumbers[row]->getNumber(col) == 0) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                } else if (retrievedNumbers[row]->getNumber(col) == 1) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                }
                rect.x = col * squareSpacingX;
                rect.y = row * squareSpacingY;
                SDL_RenderFillRect(renderer, &rect);
            }
        }



        //squareSpacing ++;

        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
            isRunning = false;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
