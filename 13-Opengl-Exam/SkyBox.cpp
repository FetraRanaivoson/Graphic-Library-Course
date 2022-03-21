//
// Created by Administrator on 8/19/2021.
//

#include "SkyBox.h"
#include "Utils.cpp"

SkyBox::SkyBox() {
    idSkyBox = Utils::loadTexture("./assets/skybox.png");
}

void SkyBox::draw() {
    Utils::drawSkybox(100,100,100, idSkyBox);
}
