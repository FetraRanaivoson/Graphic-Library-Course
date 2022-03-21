//
// Created by Administrator on 8/19/2021.
//


class Platform {
private:
    GLuint idSkyBox;
    float px, py, pz, rx, ry, rz, sx, sy,sz;

public:

    Platform();
    Platform(float px, float py, float pz, float rx, float ry, float rz,
             float sx, float sy, float sz);


    void draw();


    float getPosX() const;

    float getPosY() const;

    float getPosZ() const;

    float getRotateX() const;

    float getRotateY() const;

    float getRotateZ() const;

    float getScaleX() const;

    float getScaleY() const;

    float getScaleZ() const;


};
