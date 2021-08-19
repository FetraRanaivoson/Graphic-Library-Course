//
// Created by Fetra on 8/12/2021.
//

#include "Transform.h"




float Transform::getPosX() const {
    return posX;
}

void Transform::incrementPosX(float posX) {
    Transform::posX += cos (rotateX * M_PI / 180) * posX;
    Transform::posZ -= sin (rotateX * M_PI / 180) * posX;
}

float Transform::getPosY() const {
    return posY;
}

void Transform::setPosY(float posY) {
    Transform::posY = posY;
}

float Transform::getPosZ() const {
    return posZ;
}

void Transform::setPosZ(float posZ) {
    Transform::posZ = posZ;
}

float Transform::getScaleX() const {
    return scaleX;
}

void Transform::setScaleX(float scaleX) {
    Transform::scaleX = scaleX;
}

float Transform::getScaleY() const {
    return scaleY;
}

void Transform::setScaleY(float scaleY) {
    Transform::scaleY = scaleY;
}

float Transform::getScaleZ() const {
    return scaleZ;
}

void Transform::setScaleZ(float scaleZ) {
    Transform::scaleZ = scaleZ;
}

Transform::Transform(float posX, float posY, float posZ, float rotateX, float rotateY, float rotateZ, float scaleX,
                     float scaleY, float scaleZ) : posX(posX), posY(posY), posZ(posZ), rotateX(rotateX),
                                                   rotateY(rotateY), rotateZ(rotateZ), scaleX(scaleX), scaleY(scaleY),
                                                   scaleZ(scaleZ) {}

float Transform::getRotateX() const {
    return rotateX;
}

void Transform::setRotateX(float rotateX) {
    Transform::rotateX = rotateX;
}

float Transform::getRotateY() const {
    return rotateY;
}

void Transform::incrementRotateY() {
    Transform::rotateY +=10;
}

float Transform::getRotateZ() const {
    return rotateZ;
}

void Transform::setRotateZ(float rotateZ) {
    Transform::rotateZ = rotateZ;
}

void Transform::incrementPosY(float velocityY) {
    Transform::posY += 1 * velocityY;
}
