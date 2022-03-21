#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

SDL_Window *win;
//SDL_Renderer *render;

int width = 800, height = 600;

int main(int argc, char **args) {
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("opengl template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                           SDL_WINDOW_OPENGL);
    //SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &win, &render);

    //Opengl version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);


    //Context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);

    SDL_Event event;
    glLoadIdentity();


    while (isRunning) {

        //Clean window
//        SDL_SetRenderDrawColor(render, 0, 128, 255, 255);
//        SDL_RenderClear(render);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);  //quel memoire des couleurs est prete à être modifié


        //Event handling
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }


        //Draw any objects
//        glBegin(GL_TRIANGLES);
//        glColor3f(0,0,1);
//        glVertex2f(-0.75f, -0.75f);
//        glColor3f(0,1,0);
//        glVertex2f(0, 0.75f);
//        glColor3f(1,0,0);
//        glVertex2f(0.75f, -0.75f);
//        glEnd();

        glTranslatef(.01, .01, 0);

        glBegin(GL_LINES);
        glColor3ub(255, 0, 0);
        glVertex2f(0, 0);
        glVertex2f(.3, 0);

        glColor3ub(0, 255, 0);
        glVertex2f(0, 0);
        glVertex2f(0, .3);
        glEnd();





        //Update screen
        //SDL_RenderPresent(render);
        glFlush();
        SDL_GL_SwapWindow(win);

        //Pause image
        SDL_Delay(1);
    }

    //SDL_DestroyRenderer(render);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
                        