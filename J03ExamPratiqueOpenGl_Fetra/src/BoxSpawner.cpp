//
// Created by Administrator on 8/19/2021.
//

#include "BoxSpawner.h"

BoxSpawner::BoxSpawner(float ceilingX, float ceilingY, float ceilingZ)
        : ceilingX(ceilingX), ceilingY(ceilingY), ceilingZ(ceilingZ) {
}

void BoxSpawner::prepareBoxes() {
    posX = rand() % (int) ceilingX;
    posY = ceilingY;
    posZ = rand() % (int) ceilingZ;
    rotX = 0;
    rotY = 0;
    rotZ = 0;

    boxes.push_back(new Box(posX, posY, posZ, rotX, rotY, rotZ, sX, sY, sZ));


}

void BoxSpawner::spawnBoxes() {
    if (!boxes.empty()) {
        for (Box *box: boxes) {
            box->draw();
            box->autoFall();
        }
    }
}

