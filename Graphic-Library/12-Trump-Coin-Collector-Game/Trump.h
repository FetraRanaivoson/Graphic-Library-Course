//
// Created by Fetra on 8/16/2021.
//

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "iostream"

class Trump {
private:
    SDL_Texture* sprite;
    int wS = 0, hS = 0;
    int col = 0, row = 0;
    int wI = 0, hI = 0;

    SDL_Rect positionImg ;
    SDL_Rect positionScreen ;

    int velocity = 5;

    const Uint8 *state = nullptr;
    Uint32 currentTime = 0;
    Uint32 lastUpdate = 0;
    int deltaTime = 75;

public:

    Trump(SDL_Renderer* renderer);

    void update(SDL_Renderer* renderer);


};
