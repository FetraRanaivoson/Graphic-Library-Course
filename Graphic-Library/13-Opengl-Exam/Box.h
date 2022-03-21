//
// Created by Fetra on 8/12/2021.
//

#define _USE_MATH_DEFINES
#include <cmath>
enum Direction {FORWARD, BACKWARD, UP, DOWN, ROTATE_LEFT, ROTATE_RIGHT};

class Box {

private:
    float posX, posY, posZ;
    float rotateX,rotateY,rotateZ;
    float scaleX, scaleY, scaleZ;

    float velocity = .1;
    float fallVelocity = .05;

public:
    Box(float posX, float posY, float posZ, float rotateX, float rotateY, float rotateZ, float scaleX,
              float scaleY, float scaleZ);


    void draw();
    void move(Direction direction);
    void autoFall();
    bool collide(Box* box);

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

    virtual ~Box();

};
