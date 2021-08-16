//
// Created by Fetra on 8/12/2021.
//

#ifndef DEMOFIRSTSDL_TRANSFORM_H
#define DEMOFIRSTSDL_TRANSFORM_H

#include "cmath"

class Transform {

private:
    float posX, posY, posZ;
    float rotateX,rotateY,rotateZ;
    float scaleX, scaleY, scaleZ;

public:
    Transform(float posX, float posY, float posZ, float rotateX, float rotateY, float rotateZ, float scaleX,
              float scaleY, float scaleZ);

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

};


#endif //DEMOFIRSTSDL_TRANSFORM_H
