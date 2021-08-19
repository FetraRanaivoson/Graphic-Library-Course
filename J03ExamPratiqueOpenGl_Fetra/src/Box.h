//
// Created by Administrator on 8/19/2021.
//

#ifndef EXAMPRATIQUE_BOX_H
#define EXAMPRATIQUE_BOX_H

#include <SDL2/SDL.h>
#include "Utilities/Utils.h"
#include "Utilities/Transform.h"
enum Direction{FORWARD, BACKWARD};


class Box {
    Transform* box;
    float velocity = .01;

public:
    Box(Transform *box, float velocity);

    void draw();
    void move(Direction direction);

};


#endif //EXAMPRATIQUE_BOX_H
