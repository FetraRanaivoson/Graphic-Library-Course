#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

void drawAxis();

void drawLeftRoof(float velocityRotation, float velocityTranslationX, float velocityTranslationY);

void drawRightRoof(float velocityRotation, float velocityTranslationX, float velocityTranslationY);

void drawHomeBody(float velocityRotation, float velocityTranslationX, float velocityTranslationY);

void drawWindows(float velocityRotation, float velocityTranslationX, float velocityTranslationY);

void drawFireplace(float velocityRotation, float velocityTranslationX, float velocityTranslationY);

void getState(const Uint8 *state, float &velocityRotation, float &velocityTranslationX, float &velocityTranslationY);

int main(int argc, char **args) {
    SDL_Window *win;
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow("Maison", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
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


    float velocityRotation = 0;
    float velocityTranslationX = 0;
    float velocityTranslationY = 0;

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
        glClearColor(1.0f, 1.f, 1.f,1.f); //permet d'expliquer avec quelle couleur on va remplir la memoire des couleurs
        glClear(GL_COLOR_BUFFER_BIT); //permet de dire que la memoire des couleurs est prête à être modifié


        //gestion évènement
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        state = SDL_GetKeyboardState(NULL);
        getState(state, velocityRotation, velocityTranslationX, velocityTranslationY);

        drawLeftRoof(velocityRotation, velocityTranslationX, velocityTranslationY);
        drawRightRoof(velocityRotation, velocityTranslationX, velocityTranslationY);
        drawHomeBody(velocityRotation, velocityTranslationX, velocityTranslationY);
        drawWindows(velocityRotation, velocityTranslationX, velocityTranslationY);
        drawFireplace(velocityRotation, velocityTranslationX, velocityTranslationY);
        drawAxis();


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

void getState(const Uint8 *state, float &velocityRotation, float &velocityTranslationX, float &velocityTranslationY) {
    if (state[SDL_SCANCODE_LEFT]) {
        velocityRotation += 1;
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        velocityRotation -= 1;
    }
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
}

void drawFireplace(float velocityRotation, float velocityTranslationX, float velocityTranslationY) {
    glPopMatrix();//Pop
    glPushMatrix();//And Save for later
    glTranslatef(velocityTranslationX, velocityTranslationY,0);
    glRotatef(velocityRotation, 0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glColor3ub(0, 100, 255);
    glVertex2f(62,155);
    glVertex2f(65,160);
    glVertex2f(65,200);
    glVertex2f(90,200);
    glVertex2f(90,148);
    glEnd();
}

void drawWindows(float velocityRotation, float velocityTranslationX, float velocityTranslationY) {
    glPopMatrix();//Pop
    glPushMatrix();//And Save for later
    glTranslatef(velocityTranslationX, velocityTranslationY,0);
    glRotatef(velocityRotation, 0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glColor3ub(0, 255, 0);
    glVertex2f(0,70);
    glVertex2f(50,70);
    glVertex2f(50,30);
    glVertex2f(0,30);
    glVertex2f(0,70);
    glEnd();

    glPopMatrix();//Pop
    glPushMatrix();//And Save for later
    glTranslatef(velocityTranslationX, velocityTranslationY,0);
    glRotatef(velocityRotation, 0, 0, 1);
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);
    glVertex2f(25,70);
    glVertex2f(25,30);
    glColor3ub(100, 0, 255);
    glVertex2f(0,50);
    glVertex2f(50,50);
    glEnd();
}

void drawHomeBody(float velocityRotation, float velocityTranslationX, float velocityTranslationY) {
    glPopMatrix();//Pop
    glPushMatrix();//And Save for later
    glTranslatef(velocityTranslationX, velocityTranslationY,0);
    glRotatef(velocityRotation, 0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glColor3ub(0, 100, 255);
    glVertex2f(-100, 110);
    glVertex2f(100, 110);
    glVertex2f(100, -110);
    glVertex2f(-100, -110);
    glVertex2f(-100, 110);
    glEnd();
}

void drawRightRoof(float velocityRotation, float velocityTranslationX, float velocityTranslationY) {
    glPopMatrix();//Pop
    glPushMatrix();//And Save for later
    glTranslatef(velocityTranslationX,  velocityTranslationY,0); //translation first
    glRotatef(-15 + velocityRotation,0, 0, 1);
    glTranslatef(50 + 15,150,0); //just an offset
    glBegin(GL_LINE_STRIP);
    glColor3ub(10, 0, 255);
    glVertex2f(100, 15);
    glVertex2f(100, -15);
    glVertex2f(-100, -15);
    glVertex2f(-100, 15);
    glVertex2f(100, 15);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(255, 100, 0);
    glVertex2f(100, 15);
    glVertex2f(100, -15);
    glVertex2f(-100, -15);
    glVertex2f(-100, 15);
    glVertex2f(100, 15);
    glEnd();
}

void drawLeftRoof(float velocityRotation, float velocityTranslationX, float velocityTranslationY) {
    glPopMatrix();
    glPushMatrix();
    glTranslatef(velocityTranslationX, velocityTranslationY,0); //translation first
    glRotatef(15 + velocityRotation, 0, 0, 1); //always rotate with z=1;
    glTranslatef(-50 - 15,150,0); //just an offset
    glBegin(GL_LINE_STRIP);
    glColor3ub(10, 100, 255);
    glVertex2f(-100, 15);
    glVertex2f(100, 15);
    glVertex2f(100, -15);
    glVertex2f(-100, -15);
    glVertex2f(-100, 15);
    glEnd();
    glBegin(GL_QUADS);
    glColor3ub(255, 100, 0);
    glVertex2f(-100, 15);
    glVertex2f(100, 15);
    glVertex2f(100, -15);
    glVertex2f(-100, -15);
    glVertex2f(-100, 15);
    glEnd();
}

void drawAxis() {
    //glLoadIdentity();
    glPopMatrix();
    glPushMatrix();
    glBegin(GL_LINES);
    glColor3f(.5, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(10, 0);
    glColor3f(0, .5, 0);
    glVertex2f(0, 0);
    glVertex2f(0, 10);
    glEnd();
}

                        