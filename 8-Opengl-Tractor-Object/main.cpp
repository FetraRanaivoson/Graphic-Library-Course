#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>


void drawAxis();
void drawCircle(int resolution, int radius, int translateX);
void drawBody();
void drawWheels(float velocityRotation);
void drawShovel(float shovelRotationVelocity);
void getState(const Uint8 *state, float &velocityTranslationX, float &velocityTranslationY, float &velocityRotation,
              float &shovelRotationVelocity);
int main(int argc, char **args) {
    SDL_Window *win; 
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Tractor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    //precise la version d opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //creation du context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);
    float velocityRotation = 0;
    float velocityTranslationX = 0;
    float velocityTranslationY = 0;
    float shovelRotationVelocity = 0;
    const Uint8 *state = nullptr;
    SDL_Event event;
    glMatrixMode(GL_MODELVIEW);
    while (isRunning) {
        glLoadIdentity();

        //Clean window
        glClearColor(0.0f, 0.f, 0.f,
                     1.f); //permet d'expliquer avec quelle couleur on va remplir la memoire des couleurs
        glClear(GL_COLOR_BUFFER_BIT); //permet de dire que la memoire des couleurs est prête à être modifié

        //Handle events
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        state = SDL_GetKeyboardState(NULL);
        getState(state, velocityTranslationX, velocityTranslationY, velocityRotation, shovelRotationVelocity);

//        drawAxis();
        glTranslatef(velocityTranslationX, velocityTranslationY, 0); //Translate for future objects
        drawBody();
        drawWheels(velocityRotation);
        drawShovel(shovelRotationVelocity);
//        drawAxis();


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
void getState(const Uint8 *state, float &velocityTranslationX, float &velocityTranslationY, float &velocityRotation,
              float &shovelRotationVelocity) {
    if (state[SDL_SCANCODE_D]) {
        velocityTranslationX += 1;
        velocityRotation -= .25;
    }
    if (state[SDL_SCANCODE_A]) {
        velocityTranslationX -= 1;
        //Create Axis for the shovel
        velocityRotation += .25;
    }
    if (state[SDL_SCANCODE_W]) {
        velocityTranslationY += 1;
    }
    if (state[SDL_SCANCODE_S]) {
        velocityTranslationY -= 1;
    }
    if (state[SDL_SCANCODE_LEFT]) {
        if (shovelRotationVelocity > 70) {
            shovelRotationVelocity = 70;
        } else {
            shovelRotationVelocity += 1;
        }
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        if (shovelRotationVelocity < -70) {
            shovelRotationVelocity = -70;
        } else {
            shovelRotationVelocity -= 1;
        }
    }
}
void drawShovel(float shovelRotationVelocity) {
    glPushMatrix();
    //Create Axis for the shovel
    glTranslatef(75, 100, 0);
    glBegin(GL_LINES);
    glColor3f(.5, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(20, 0);
    glColor3f(0, .5, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 20);
    glEnd();
    //glTranslatef(velocityTranslationX, velocityTranslationY, 0);
    glRotatef(shovelRotationVelocity, 0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glColor3ub(255, 200, 0);
    glVertex2f(0, 0);
    glVertex2f(75, 75);
    glVertex2f(100, 75);
    glVertex2f(125, 60);
    glVertex2f(100, 30);//
    glVertex2f(80, 45);///
    glVertex2f(100, 65);
    glVertex2f(85, 65);
    glVertex2f(10, -10);
    glVertex2f(0, 0);
    glEnd();

    glPopMatrix();
}
void drawWheels(float velocityRotation) {
    glPushMatrix();

    glTranslatef(-100, 0, 0);
    int resolution = 100;
    int radius = 50;
    int translateX = -100;

    glPushMatrix();
    glRotatef(velocityRotation, 0, 0, 1);
    drawCircle(resolution, radius, translateX);
    glPopMatrix();

    glTranslatef(+175, 0, 0);
    drawAxis();
    //glRotatef(velocityRotation,0,0,1);
//    translateX = 75;
    glPushMatrix();
    glRotatef(velocityRotation, 0, 0, 1);
    drawCircle(resolution, radius, translateX);
    glPopMatrix();

    glPopMatrix();
    //drawAxis();
}
void drawBody() {
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    glColor3ub(255, 200, 0);
    glVertex2f(-100, 100);
    glVertex2f(0, 100);
    glVertex2f(0, 175);
    glVertex2f(75, 100);
    glVertex2f(75, 0);
    glVertex2f(-100, 0);
    glVertex2f(-100, 100);
    glEnd();
    glPopMatrix();
}
void drawCircle(int resolution, int radius, int translateX) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < resolution; i++) {
        // 2M_PI                ----> Point #15
        // theta increment?     <---- Point #1
        float theta = 2.0f * M_PI * float(i) / float(resolution);//get the current angle
        if (i % 2 == 0)
            radius = 45;
        float x = radius * cosf(theta);//calculate the x component
        float y = radius * sinf(theta);//calculate the y component
        glVertex2f(x, y);//output vertex
        radius = 50;
    }
    glEnd();
}
void drawAxis() {
    //glLoadIdentity();
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(.5, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(20, 0);
    glColor3f(0, .5, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 20);
    glEnd();
    glPopMatrix();
}
                        