#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

void drawAxis();

void drawCircle(int resolution, int radius, int translateX);

void drawBody(float velocityTranslationX, float velocityTranslationY);

void drawWheels(float velocityTranslationX, float velocityTranslationY, float velocityRotation);

void drawShovel(float velocityTranslationX, float velocityTranslationY, float shovelRotationVelocity);

void getState(const Uint8 *state, float &velocityTranslationX, float &velocityTranslationY, float &shovelRotationVelocity);

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
    while (isRunning) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //Clean window
        glClearColor(0.0f, 0.f, 0.f,1.f); //permet d'expliquer avec quelle couleur on va remplir la memoire des couleurs
        glClear(GL_COLOR_BUFFER_BIT); //permet de dire que la memoire des couleurs est prête à être modifié

        //Handle events
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        state = SDL_GetKeyboardState(NULL);
        getState(state, velocityTranslationX, velocityTranslationY, shovelRotationVelocity);

        drawAxis();
        drawBody(velocityTranslationX, velocityTranslationY);
        drawWheels(velocityTranslationX, velocityTranslationY, velocityRotation);
        drawShovel(velocityTranslationX, velocityTranslationY, shovelRotationVelocity);
        drawAxis();


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

void getState(const Uint8 *state, float &velocityTranslationX, float &velocityTranslationY, float &shovelRotationVelocity) {
    if (state[SDL_SCANCODE_D]) {
        velocityTranslationX += 1;
    }
    if (state[SDL_SCANCODE_A]) {
        velocityTranslationX -= 1;
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
            shovelRotationVelocity = - 70;
        }  else {
            shovelRotationVelocity -= 1;
        }
    }
}

void drawShovel(float velocityTranslationX, float velocityTranslationY, float shovelRotationVelocity) {
    glPopMatrix();
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

    glTranslatef(velocityTranslationX, velocityTranslationY, 0);
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

}

void drawWheels(float velocityTranslationX, float velocityTranslationY, float velocityRotation) {
    glPopMatrix();
    glPushMatrix();
    glTranslatef(velocityTranslationX, velocityTranslationY, 0);
    glBegin(GL_LINE_LOOP);
    int resolution = 100;
    int radius = 25;
    int translateX = -100;
    drawCircle(resolution, radius, translateX);
    glEnd();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(velocityTranslationX, velocityTranslationY, 0);
    glBegin(GL_LINE_LOOP);
    translateX = 75;
    drawCircle(resolution, radius, translateX);
    glEnd();
}

void drawBody(float velocityTranslationX, float velocityTranslationY) {
    glPopMatrix();
    glPushMatrix();
    glTranslatef(velocityTranslationX, velocityTranslationY, 0);
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
}

void drawCircle(int resolution, int radius, int translateX) {
    for (int i = 0; i < resolution; i++) {
        // 2M_PI                ----> Point #15
        // theta increment?     <---- Point #1
        float theta = 2.0f * M_PI * float(i) / float(resolution);//get the current angle
        float x = radius * cosf(theta);//calculate the x component
        float y = radius * sinf(theta);//calculate the y component
        glVertex2f(x + translateX, y);//output vertex
    }
}

void drawAxis() {
    //glLoadIdentity();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(.5, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(20, 0);
    glColor3f(0, .5, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 20);
    glEnd();
}
                        