//
// Created by jlidou on 2021-08-12.
//

#ifndef DEMOFIRSTSDL_UTILS_H
#define DEMOFIRSTSDL_UTILS_H

#include <GL/GL.h>

void drawAxis(float taille) {


    glPushMatrix();

    glScaled(taille, taille, taille);
    glLineWidth(2);
    glBegin(GL_LINES);
    //axe des x
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    //axe des y
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    //axe des x
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
    glLineWidth(1);

    glPopMatrix();

}

void drawQuad(float width, float height) {

    glPushMatrix();



    glScalef(width, height, 1);
    glBegin(GL_QUADS);
    glColor3f(0, 1, 1);
    glVertex2f(0, 0);
    glVertex2f(1, 0);
    glVertex2f(1, 1);
    glVertex2f(0, 1);
    glEnd();

    glPopMatrix();

}

void drawCube(float translateX, float translateY, float translateZ, float rotateX, float rotateY, float rotateZ,
              float scaleX, float scaleY, float scaleZ) {

    glPushMatrix();
    glTranslatef(translateX, translateY, translateZ);
    glRotatef(rotateY, 0, 1, 0);
    drawAxis(2);

    //glScalef(scaleX, scaleY, scaleZ);

    //face du bas
    glBegin(GL_QUADS);
    glColor3f(.1, .1, 0.1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    //face du gauche
    glColor3f(.1, .1, .1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    //face du gauche
    glColor3f(.15, .15, 0.15);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);

    //face du droite
    glColor3f(.1, .1, 0.1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

//    //face du droite
    glColor3f(.15, .15, 0.15);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

//    //face du droite
    glColor3f(.5, .5, 0.5);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glEnd();

    glPopMatrix();
}
void drawCube(float tailleX, float tailleY, float tailleZ) {
    glPushMatrix();
    glScalef(tailleX, tailleY, tailleZ);
    glBegin(GL_QUADS);
    //face du bas
    glColor3f(0.1, 0.1, 0.1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    //face du gauche
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    //face du gauche
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);

    //face du droite
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    //face du droite
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

    //face du droite
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glEnd();
    glPopMatrix();
}

#endif //DEMOFIRSTSDL_UTILS_H
