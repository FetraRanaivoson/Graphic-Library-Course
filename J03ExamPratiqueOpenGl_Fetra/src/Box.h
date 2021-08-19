//
// Created by Fetra on 8/12/2021.
//

#ifndef DEMOFIRSTSDL_BOX_H
#define DEMOFIRSTSDL_BOX_H

#include "cmath"
#include "Utils.h"


enum Direction {FORWARD, BACKWARD, UP, DOWN, ROTATE_LEFT, ROTATE_RIGHT};
class Box {

private:
    float posX, posY, posZ;
    float rotateX,rotateY,rotateZ;
    float scaleX, scaleY, scaleZ;

    float velocity = .1;
    float fallVelocity = .1;

public:
    Box(float posX, float posY, float posZ, float rotateX, float rotateY, float rotateZ, float scaleX,
              float scaleY, float scaleZ);


    void draw();
    void move(Direction direction);
    void autoFall();

    float getPosX() const;
    void incrementPosX(float posX);
    float getPosY() const;
    void setPosY(float posY);

    float getRotateX() const;
    void setRotateX(float rotateX);
    float getRotateY() const;
    void incrementRotateY();
    float getRotateZ() const;

    void setRotateZ(float rotateZ);
    float getPosZ() const;
    void setPosZ(float posZ);
    float getScaleX() const;
    void setScaleX(float scaleX);
    float getScaleY() const;
    void setScaleY(float scaleY);
    float getScaleZ() const;
    void setScaleZ(float scaleZ);

    void incrementPosY(float velocityY);

};


#endif //DEMOFIRSTSDL_BOX_H
