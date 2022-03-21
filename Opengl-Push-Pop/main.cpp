#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

void drawAxis();

int main(int argc, char **args) {
    SDL_Window *win;
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("opengl Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                           SDL_WINDOW_OPENGL);

    //precise la version d opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //creation du context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);

    float angleG = 0;
    float angleD = 0;


    const Uint8 *state = nullptr;

    glLineWidth(2);
    float roofPositionX = 100;
    //float roofPositionY = 100;
    float roofLength = 150;
    float roofWidth = 30;

    SDL_Event event;
    while (isRunning) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //Nettoyer la fenêtre
        glClearColor(0.0f, 0.f, 0.f,
                     1.f); //permet d'expliquer avec quelle couleur on va remplir la memoire des couleurs
        glClear(GL_COLOR_BUFFER_BIT); //permet de dire que la memoire des couleurs est prête à être modifié


        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }


        state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT]) {
            angleG += 1;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            angleD += 1;
        }

        //Draw any
        glPushMatrix();//1st always push: work with the matrix current state
        glRotatef(angleG, 0, 0, 1);
        glBegin(GL_LINE_STRIP);
        glColor3ub(0, 0, 255);
        glVertex2f(-100, 15);
        glVertex2f(100, 15);
        glVertex2f(100, -15);
        glVertex2f(-100, -15);
        glVertex2f(-100, 15);
        glEnd();
        glBegin(GL_QUADS);
        glColor3ub(255, 0, 0);
        glVertex2f(-100, 15);
        glVertex2f(100, 15);
        glVertex2f(100, -15);
        glVertex2f(-100, -15);
        glVertex2f(-100, 15);
        glEnd();


        glPopMatrix();//2nd etc pop: pop  matrix from the pile and work w it
        glRotatef(-angleD, 0, 0, 1);
        glBegin(GL_LINE_STRIP);
        glColor3ub(0, 0, 255);
        glVertex2f(100, 15);
        glVertex2f(100, -15);
        glVertex2f(-100, -15);
        glVertex2f(-100, 15);
        glVertex2f(100, 15);
        glEnd();
        glBegin(GL_QUADS);
        glColor3ub(255, 0, 0);
        glVertex2f(100, 15);
        glVertex2f(100, -15);
        glVertex2f(-100, -15);
        glVertex2f(-100, 15);
        glVertex2f(100, 15);
        glEnd();


        glPopMatrix();//2nd etc pop
        drawAxis();
        //glPushMatrix();


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

void drawAxis() {
    //glLoadIdentity();
    glBegin(GL_LINES);
    glColor3f(.5, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(100, 0);
    glColor3f(0, .5, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 100);
    glEnd();
}

                        