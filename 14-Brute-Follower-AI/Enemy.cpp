//
// Created by Administrator on 8/17/2021.
//

#include "Enemy.h"


Enemy::Enemy(GLUquadric *params) {

    enemyID = glGenLists(1);
    glNewList(enemyID, GL_COMPILE);
    glColor3ub(255, 5, 5);

    gluQuadricDrawStyle(params, GLU_LINE);
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glRotatef(90, 1, 0, 0);
    gluSphere(params, 2, 6, 6);
    glPopMatrix();

    gluQuadricDrawStyle(params, GLU_LINE);
    glPushMatrix();
    glTranslatef(0, 5, 0);
    glRotatef(90, 1, 0, 0);
    gluSphere(params, 1, 6, 6);
    glPopMatrix();

    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 5, 0);
    glRotatef(0, 1, 0, 0);
    glColor3ub(50, 50, 50);
    gluCylinder(params, 1, .01, 5, 10, 10);
    glPopMatrix();

    glEndList();
}


void Enemy::draw() const {
    glPopMatrix();
    glTranslatef(enemyPosX, enemyPosY, enemyPosZ);
    //glCallList(enemyID);
    glPopMatrix();
}

void Enemy::trackPlayer(float x, float y, float z) {

    currentX = enemyPosX;
    currentZ = enemyPosZ;

    Vector *playerCoordinates = new Vector(x, y, z);
    //(b-a).normalize
    Vector direction = playerCoordinates->operator-(Vector(enemyPosX, enemyPosY, enemyPosZ));
    direction.normalize();


    float cosinus = direction.z / direction.magnitude();
    //float sinus = direction.x / direction.magnitude();

//    if (z > 0)
//        rotationAngle = -acos(cosinus) * 180 / M_PI;
//    if (z <= 0)
//        rotationAngle =   acos(cosinus) * 180 / M_PI + 90;

    if (deltaX() > 0 && deltaZ() < 0 || deltaX() > 0 && deltaZ() > 0) {
        rotationAngle = acos(cosinus) * 180 / M_PI;
        lastX = currentX;
        lastZ = currentZ;
    }
    if (deltaX() < 0 && deltaZ() < 0 || deltaX() < 0 && deltaZ() > 0) {
        rotationAngle = -acos(cosinus) * 180 / M_PI;
        lastX = currentX;
        lastZ = currentZ;
    }



    //std::cout << rotationAngle << std::endl;

    glPushMatrix();
    glRotatef(rotationAngle, 0, 1, 0);
    //glTranslatef(cosinus,0, -sinus);
    glCallList(enemyID);

    enemyPosX += velocity * direction.x;
//    enemyPosY += velocity * direction.y;
    enemyPosZ += velocity * direction.z;

    glPopMatrix();
}

float Enemy::deltaZ() const { return currentZ - lastZ; }

float Enemy::deltaX() const { return currentX - lastX; }

Enemy::~Enemy() {
    glDeleteLists(enemyID, 1);
}



