//
// Created by Fetra on 8/12/2021.
//

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

    float getPosZ() const;

    void setPosZ(float posZ);

    float getScaleX() const;

    void setScaleX(float scaleX);

    float getScaleY() const;

    void setScaleY(float scaleY);

    float getScaleZ() const;

    void setScaleZ(float scaleZ);

};


