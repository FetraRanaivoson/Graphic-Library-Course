//
// Created by Administrator on 8/19/2021.
//

#include "Box.h"

Box::Box(Transform *box, float velocity) : box(box), velocity(velocity) {}



void Box::draw() {
    drawCube(box->getPosX(), box->getPosY(), box->getPosZ(),
             box->getRotateX(),box->getRotateY(),box->getRotateZ(),
             box->getScaleX(), box->getScaleY(), box->getScaleZ());
}

void Box::move(Direction direction) {
    if (direction == FORWARD) {
        box->incrementPosX(velocity);
    }
    if (direction == BACKWARD) {
        box->incrementPosX(-velocity);
    }
    if (direction == UP) {
        
    }
}

