#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

#include <vector>

SDL_Window *win;
SDL_Renderer *renderer;
int width = 800, height = 600;


void createMenuPanel(SDL_Rect &menu, SDL_Rect &redPencil, SDL_Rect &bluePencil, SDL_Rect &greenPencil,
                     SDL_Rect &yellowPencil, SDL_Rect &canvas, SDL_Rect &squareTool, SDL_Rect &lineTool);

void displayMenuPanel(SDL_Rect &menu, SDL_Rect &redPencil, SDL_Rect &bluePencil, SDL_Rect &greenPencil,
                      SDL_Rect &yellowPencil, SDL_Rect &canvas, SDL_Rect &squareTool, SDL_Rect &lineTool);

bool redPencilSelected(const SDL_Rect &redPencil, int x, int y);

bool bluePencilSelected(const SDL_Rect &bluePencil, int x, int y);

bool greenPencilSelected(const SDL_Rect &greenPencil, int x, int y);

bool yellowPencilSelected(const SDL_Rect &yellowPencil, int x, int y);

bool squareToolSelected(const SDL_Rect &squareTool, int x, int y);

bool lineToolSelected(const SDL_Rect &lineTool, int x, int y);


bool menuPanelSelected(const SDL_Rect &menuBar, int x, int y);

bool onCanvas(const SDL_Rect &menuBar, int x, int y);


SDL_Color &getColorToDraw(const SDL_Rect &redPencil, const SDL_Rect &bluePencil, const SDL_Rect &greenPencil,
                          const SDL_Rect &yellowPencil, int x, int y, SDL_Color &colorToDraw);

bool onTools(const SDL_Rect &menuBar, int pointStartX, int pointStartY);

bool firstClick(const SDL_Event &event, bool firstPointPlaced);

bool anyClick(const SDL_Event &event);

bool secondClick(const SDL_Event &event, bool firstPointPlaced);

bool drawOneLine(std::vector<SDL_Point> &points);

bool drawFourLines(std::vector<SDL_Point> &points);

void checkSelectedTool(const SDL_Rect &squareTool, const SDL_Rect &lineTool, int pointStartX, int pointStartY,
                       bool &isLineToolActive, bool &isSquareToolActive, bool &isFirstPointPlaced);

void enableDrawings(bool isLineToolActive, bool isSquareToolActive, bool &isFirstPointPlaced, std::vector<SDL_Point> &points);

int main(int argc, char **args) {

    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &renderer);

    SDL_Rect menuBar;
    SDL_Rect canvas;
    SDL_Rect redPencil;
    SDL_Rect bluePencil;
    SDL_Rect greenPencil;
    SDL_Rect yellowPencil;
    SDL_Rect squareTool;
    SDL_Rect lineTool;
    createMenuPanel(menuBar, redPencil, bluePencil, greenPencil, yellowPencil, canvas, squareTool, lineTool);


    SDL_Event event;
    const Uint8 *state = 0;


    bool isFirstPointPlaced = false;
    SDL_Rect rect;
    SDL_Color colorToDraw = {255, 0, 0, 255};


    std::vector<SDL_Point> points;
    SDL_Point p1;
    SDL_Point p2;
    int pointStartX, pointStartY;
    int pointEndX, pointEndY;
    Uint32 clickedArea;


    bool isLineToolActive = true;
    bool isSquareToolActive = false;


    while (isRunning) {
//        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
//        SDL_RenderClear(renderer);

        displayMenuPanel(menuBar, redPencil, bluePencil, greenPencil, yellowPencil, canvas, squareTool, lineTool);

        while (SDL_PollEvent(&event)) {
            if (anyClick(event)) {
                clickedArea = SDL_GetMouseState(&pointStartX, &pointStartY);
                if (onTools(menuBar, pointStartX, pointStartY)) {
                    colorToDraw = getColorToDraw(redPencil, bluePencil, greenPencil, yellowPencil, pointStartX, pointStartY, colorToDraw);
                    checkSelectedTool(squareTool, lineTool, pointStartX, pointStartY, isLineToolActive, isSquareToolActive, isFirstPointPlaced);
                }
            }

            if (firstClick(event, isFirstPointPlaced)) {
                clickedArea = SDL_GetMouseState(&pointStartX, &pointStartY);
                if (onCanvas(menuBar, pointStartX, pointStartY)) {
                    p1.x = pointStartX;
                    p1.y = pointStartY;
                    points.push_back(p1);
                    isFirstPointPlaced = true;
                }

            } else if (secondClick(event, isFirstPointPlaced)) {
                clickedArea = SDL_GetMouseState(&pointEndX, &pointEndY);
                if (onCanvas(menuBar, pointEndX, pointEndY)) {
                    p2.x = pointEndX;
                    p2.y = pointEndY;
                    points.push_back(p2);
                }
            }
        }



        SDL_SetRenderDrawColor(renderer, colorToDraw.r, colorToDraw.g, colorToDraw.b, colorToDraw.a);
        enableDrawings(isLineToolActive, isSquareToolActive, isFirstPointPlaced, points);



        state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_ESCAPE])
            isRunning = false;

        SDL_Delay(15);
        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}

void enableDrawings(bool isLineToolActive, bool isSquareToolActive, bool &isFirstPointPlaced, std::vector<SDL_Point> &points) {
    if (isLineToolActive) {
        isFirstPointPlaced = drawOneLine(points);
        //isSquareToolActive = false;
    }

    if (isSquareToolActive) {
        isFirstPointPlaced = drawFourLines(points);
        //isLineToolActive = false;
    }

}

void checkSelectedTool(const SDL_Rect &squareTool, const SDL_Rect &lineTool, int pointStartX, int pointStartY,
                       bool &isLineToolActive, bool &isSquareToolActive, bool &isFirstPointPlaced) {
    if (lineToolSelected(lineTool, pointStartX, pointStartY)) {
        SDL_Log("Line tool selected");
        isLineToolActive = true;
        isSquareToolActive = false;
        //isFirstPointPlaced = false;
    }
    if (squareToolSelected(squareTool, pointStartX, pointStartY)) {
        SDL_Log("Square tool selected");
        isSquareToolActive = true;
        isLineToolActive = false;
        //isFirstPointPlaced = false;
    }
}

bool drawFourLines(std::vector<SDL_Point> &points) {
    bool isFirstPointPlaced;
    if (points.size() == 4) {
        SDL_Point pointArray[4] = {points[0], points[1], points[2], points[3]};
        SDL_RenderDrawLines(renderer, pointArray, 4);
        SDL_RenderDrawLine(renderer, pointArray[3].x, pointArray[3].y, pointArray[0].x, pointArray[0].y);
        points.clear();
        isFirstPointPlaced = false;
    }
    return isFirstPointPlaced;
}

bool drawOneLine(std::vector<SDL_Point> &points) {
    bool isFirstPointPlaced;
    if (points.size() == 2) {
        SDL_RenderDrawLine(renderer, points[0].x, points[0].y, points[1].x, points[1].y);
        points.clear();
        isFirstPointPlaced = false;
    }
    return isFirstPointPlaced;
}

bool secondClick(const SDL_Event &event, bool firstPointPlaced) {
    return event.type == SDL_MOUSEBUTTONDOWN && firstPointPlaced;
}

bool anyClick(const SDL_Event &event) { return event.type == SDL_MOUSEBUTTONDOWN; }

bool firstClick(const SDL_Event &event, bool firstPointPlaced) {
    return event.type == SDL_MOUSEBUTTONDOWN && !firstPointPlaced;
}

bool onTools(const SDL_Rect &menuBar, int pointStartX, int pointStartY) {
    return menuPanelSelected(menuBar, pointStartX, pointStartY);
}

SDL_Color &getColorToDraw(const SDL_Rect &redPencil, const SDL_Rect &bluePencil, const SDL_Rect &greenPencil,
                          const SDL_Rect &yellowPencil, int x, int y, SDL_Color &colorToDraw) {
    if (redPencilSelected(redPencil, x, y)) {
        SDL_Log("Red selected");
        // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
        colorToDraw.r = 255;
        colorToDraw.g = 0;
        colorToDraw.b = 0;
    }
    if (bluePencilSelected(bluePencil, x, y)) {
        SDL_Log("Blue selected");
        // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
        colorToDraw.r = 0;
        colorToDraw.g = 0;
        colorToDraw.b = 255;
    }
    if (greenPencilSelected(greenPencil, x, y)) {
        SDL_Log("Green selected");
        // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        colorToDraw.r = 0;
        colorToDraw.g = 255;
        colorToDraw.b = 0;
    }
    if (yellowPencilSelected(yellowPencil, x, y)) {
        SDL_Log("Yellow selected");
        //SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
        colorToDraw.r = 255;
        colorToDraw.g = 255;
        colorToDraw.b = 0;
    }
    return colorToDraw;
}

bool menuPanelSelected(const SDL_Rect &menuBar, int x, int y) {
    return x >= menuBar.x && x < menuBar.x + menuBar.w && y >= menuBar.y &&
           y < menuBar.y + menuBar.h;
}

bool onCanvas(const SDL_Rect &menuBar, int x, int y) {
    return x > menuBar.x + menuBar.w;
}

bool yellowPencilSelected(const SDL_Rect &yellowPencil, int x, int y) {
    return x > yellowPencil.x
           && x < yellowPencil.x + yellowPencil.w
           && y > yellowPencil.y
           && y < yellowPencil.y + yellowPencil.h;
}

bool greenPencilSelected(const SDL_Rect &greenPencil, int x, int y) {
    return x > greenPencil.x
           && x < greenPencil.x + greenPencil.w
           && y > greenPencil.y
           && y < greenPencil.y + greenPencil.h;
}

bool bluePencilSelected(const SDL_Rect &bluePencil, int x, int y) {
    return x > bluePencil.x
           && x < bluePencil.x + bluePencil.w
           && y > bluePencil.y
           && y < bluePencil.y + bluePencil.h;
}

bool redPencilSelected(const SDL_Rect &redPencil, int x, int y) {
    return x > redPencil.x
           && x < redPencil.x + redPencil.w
           && y > redPencil.y
           && y < redPencil.y + redPencil.h;
}

bool squareToolSelected(const SDL_Rect &squareTool, int x, int y) {
    return x > squareTool.x
           && x < squareTool.x + squareTool.w
           && y > squareTool.y
           && y < squareTool.y + squareTool.h;
}

bool lineToolSelected(const SDL_Rect &lineTool, int x, int y) {
    return x > lineTool.x
           && x < lineTool.x + lineTool.w
           && y > lineTool.y
           && y < lineTool.y + lineTool.h;
}

void displayMenuPanel(SDL_Rect &menu, SDL_Rect &redPencil, SDL_Rect &bluePencil, SDL_Rect &greenPencil,
                      SDL_Rect &yellowPencil, SDL_Rect &canvas, SDL_Rect &squareTool, SDL_Rect &lineTool) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
    SDL_RenderFillRect(renderer, &menu);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderFillRect(renderer, &redPencil);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderFillRect(renderer, &bluePencil);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_RenderFillRect(renderer, &greenPencil);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 0);
    SDL_RenderFillRect(renderer, &yellowPencil);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawRect(renderer, &squareTool);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    //SDL_RenderDrawRect(renderer, &lineTool);
    SDL_RenderDrawLine(renderer, lineTool.x, lineTool.y, lineTool.x + lineTool.w, lineTool.y + lineTool.h);


}

void createMenuPanel(SDL_Rect &menu, SDL_Rect &redPencil, SDL_Rect &bluePencil, SDL_Rect &greenPencil,
                     SDL_Rect &yellowPencil, SDL_Rect &canvas, SDL_Rect &squareTool, SDL_Rect &lineTool) {
    menu.x = 0;
    menu.y = 0;
    menu.w = width / 10;
    menu.h = height;

    canvas.x = menu.w;
    canvas.y = 0;
    canvas.w = width - menu.w;
    canvas.h = height;

    redPencil.x = 20;
    redPencil.y = 20;
    redPencil.w = menu.w / 2;
    redPencil.h = menu.w / 2;

    bluePencil.x = 20;
    bluePencil.y = redPencil.y + 60;
    bluePencil.w = menu.w / 2;
    bluePencil.h = menu.w / 2;

    greenPencil.x = 20;
    greenPencil.y = bluePencil.y + 60;
    greenPencil.w = menu.w / 2;
    greenPencil.h = menu.w / 2;

    yellowPencil.x = 20;
    yellowPencil.y = greenPencil.y + 60;
    yellowPencil.w = menu.w / 2;
    yellowPencil.h = menu.w / 2;

    squareTool.x = 20;
    squareTool.y = yellowPencil.y + 120;
    squareTool.w = menu.w / 2;
    squareTool.h = menu.w / 2;

    lineTool.x = 20;
    lineTool.y = squareTool.y + 60;
    lineTool.w = menu.w / 2;
    lineTool.h = menu.w / 2;
}



