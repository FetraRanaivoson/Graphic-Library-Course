//
// Created by Fetra on 8/12/2021.
//

#include "Box.h"
#include "Utils.cpp"




float Box::getPosX() const {
    return posX;
}

void Box::incrementPosX(float posX) {
    Box::posX += cos (rotateX * M_PI / 180) * posX;
    Box::posZ -= sin (rotateX * M_PI / 180) * posX;
}

float Box::getPosY() const {
    return posY;
}

void Box::setPosY(float posY) {
    Box::posY = posY;
}

float Box::getPosZ() const {
    return posZ;
}

void Box::setPosZ(float posZ) {
    Box::posZ = posZ;
}

float Box::getScaleX() const {
    return scaleX;
}

void Box::setScaleX(float scaleX) {
    Box::scaleX = scaleX;
}

float Box::getScaleY() const {
    return scaleY;
}

void Box::setScaleY(float scaleY) {
    Box::scaleY = scaleY;
}

float Box::getScaleZ() const {
    return scaleZ;
}

void Box::setScaleZ(float scaleZ) {
    Box::scaleZ = scaleZ;
}

Box::Box(float posX, float posY, float posZ, float rotateX, float rotateY, float rotateZ, float scaleX,
                     float scaleY, float scaleZ) : posX(posX), posY(posY), posZ(posZ), rotateX(rotateX),
                                                   rotateY(rotateY), rotateZ(rotateZ), scaleX(scaleX), scaleY(scaleY),
                                                   scaleZ(scaleZ) {}

float Box::getRotateX() const {
    return rotateX;
}

void Box::setRotateX(float rotateX) {
    Box::rotateX = rotateX;
}

float Box::getRotateY() const {
    return rotateY;
}

void Box::incrementRotateY() {
    Box::rotateY +=10;
}

float Box::getRotateZ() const {
    return rotateZ;
}

void Box::setRotateZ(float rotateZ) {
    Box::rotateZ = rotateZ;
}

void Box::incrementPosY(float velocityY) {
    Box::posY += 1 * velocityY;
}

void Box::draw() {
    Utils::drawCube(posX, posY, posZ,0, getRotateX(), 0,
                    scaleX, scaleY, scaleZ);
}

void Box::move(Direction direction) {
    if (direction == FORWARD) {
        incrementPosX(velocity);
    }
    if (direction == BACKWARD) {
        incrementPosX(-velocity);
    }
    if (direction == UP) {
        incrementPosY(velocity);
    }
    if (direction == DOWN) {
        incrementPosY(-velocity);
    }
    if (direction == ROTATE_LEFT) {
        setRotateX(rotateX + 1);
    }
    if (direction == ROTATE_RIGHT) {
        setRotateX(rotateX - 1);
    }
}

void Box::autoFall() {
    posY -= fallVelocity;
}

bool Box::collide(Box* box) {
    return box->getPosX() > posX
    && box->getPosX() + box->getScaleX() < posX + scaleX
    && box->getPosY() > posY
    && box->getPosY() + box->getScaleY() < posY + scaleY
    && box->getPosZ() > posZ
    && box->getPosZ() + box->getScaleZ() < posZ + scaleZ;
}

Box::~Box() {

}
