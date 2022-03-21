#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window *win;
SDL_Renderer *render;
int width = 800, height = 600;

SDL_Rect &manageScreenPosition(SDL_Rect &screenPosition, const Uint8 *state, int characterVelocity, int deltaTime);

int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &render);

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Surface *surfaceTemp = IMG_Load("./deadPool.png");
    int wI, hI;

    SDL_Texture *deadPoolImg = nullptr;
    if (!surfaceTemp) {
        SDL_Log("Character image loading failed");
    } else {
        //Transform surface to texture
        deadPoolImg = SDL_CreateTextureFromSurface(render, surfaceTemp);
        //Once surface is loaded, keep track of its width and height (the *srRect)
        wI = surfaceTemp->w;
        hI = surfaceTemp->h;
    }

    //Now create a rectangle to initialize the size of the *srRect (source)
    SDL_Rect sourcePosition;
    sourcePosition.x = 0;
    sourcePosition.y = 0;
    sourcePosition.w = wI;
    sourcePosition.h = hI;

    //Create a rectangle for the size of the *drRect (screen)
    SDL_Rect screenPosition;
    screenPosition.x = 0;
    screenPosition.y = 0;
    screenPosition.w = wI / 7;
    screenPosition.h = hI / 7;
    SDL_FreeSurface(surfaceTemp);


    const Uint8 *state;
    int characterVelocity = 1;

    int deltaTime = 0;
    int fps;
    Uint32 currentTime;
    currentTime = SDL_GetTicks();
    Uint32 lastUpdate;


    SDL_Event event;
    while (isRunning) {
        lastUpdate = currentTime;

        //Clean window
        SDL_SetRenderDrawColor(render, 52, 102, 163, 255);
        SDL_RenderClear(render);

        //Event handling
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        state = SDL_GetKeyboardState(NULL);
        screenPosition = manageScreenPosition(screenPosition, state, characterVelocity, deltaTime);


        //Draw any objects
        //*sRect: source (surfaceTemp)
        //*dRect: screen (NULL if I want source image to always cover entire screen)
        SDL_RenderCopy(render, deadPoolImg, &sourcePosition, &screenPosition);

        //Pause image
        SDL_Delay(15);
        //Update screen
        SDL_RenderPresent(render);

        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastUpdate;
        fps = 1000 / deltaTime;
    }

    SDL_DestroyTexture(deadPoolImg);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

SDL_Rect &manageScreenPosition(SDL_Rect &screenPosition, const Uint8 *state, int characterVelocity, int deltaTime) {
    if (state[SDL_SCANCODE_LEFT]) {
        screenPosition.x -= characterVelocity * deltaTime;
    }

    if (state[SDL_SCANCODE_RIGHT]) {
        screenPosition.x += characterVelocity * deltaTime;
    }

    if (state[SDL_SCANCODE_DOWN]) {
        screenPosition.y += characterVelocity * deltaTime;
    }

    if (state[SDL_SCANCODE_UP]) {
        screenPosition.y -= characterVelocity * deltaTime;
    }

    if (screenPosition.x > width){
        screenPosition.x = 0;
    }
    if (screenPosition.x < 0){
        screenPosition.x = width;
    }

    if (screenPosition.y > height){
        screenPosition.y = 0;
    }
    if (screenPosition.y < 0){
        screenPosition.y = height;
    }


        return screenPosition;
}
                        