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


    //GETTERS
    float getPosX() const;
    float getPosY() const;
    float getPosZ() const;
    float getRotateX() const;
    float getRotateY() const;
    float getRotateZ() const;
    float getScaleX() const;
    float getScaleY() const;
    float getScaleZ() const;



    //SETTERS
    void setPosX(float posX);
    void setPosY(float posY);
    void setPosZ(float posZ);
    void setRotateX(float rotateX);
    void setRotateY(float rotateY);
    void setRotateZ(float rotateZ);
    void setScaleX(float scaleX);
    void setScaleY(float scaleY);
    void setScaleZ(float scaleZ);


    void incrementPosX(float posX);
    void incrementRotateY();
    
};


#endif //DEMOFIRSTSDL_TRANSFORM_H
