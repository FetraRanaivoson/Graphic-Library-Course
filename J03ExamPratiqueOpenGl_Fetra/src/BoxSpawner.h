//
// Created by Administrator on 8/19/2021.
//

#ifndef DEMOFIRSTSDL_BOXSPAWNER_H
#define DEMOFIRSTSDL_BOXSPAWNER_H

#include <vector>
#include "Box.h"

class BoxSpawner {

    std::vector <Box*> boxes;
    float ceilingX, ceilingY, ceilingZ;

    float posX = 0;
    float posY = 0;
    float posZ = 0;
    float rotX = 0;
    float rotY = 0;
    float rotZ = 0;
    float sX = 3;
    float sY = 3;
    float sZ = 3;

public:
    BoxSpawner(float ceilingX, float ceilingY, float ceilingZ);
    void prepareBoxes();
    void spawnBoxes();
};


#endif //DEMOFIRSTSDL_BOXSPAWNER_H
