//
// Created by Administrator on 8/19/2021.
//

#include "Platform.h"

Platform::Platform() {}

Platform::Platform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz)
        : px(px), py(py), pz(pz), rx(rx), ry(ry),
          rz(rz), sx(sx), sy(sy), sz(sz) {}

float Platform::getPosX() const {
    return px;
}

float Platform::getPosY() const {
    return py;
}

float Platform::getPosZ() const {
    return pz;
}

float Platform::getRotateX() const {
    return rx;
}

float Platform::getRotateY() const {
    return ry;
}

float Platform::getRotateZ() const {
    return rz;
}

float Platform::getScaleX() const {
    return sx;
}

float Platform::getScaleY() const {
    return sy;
}

float Platform::getScaleZ() const {
    return sz;
}

void Platform::draw() {
    Utils::drawCube(px, py, pz,rx, ry, rz,sx, sy, sz);
}
