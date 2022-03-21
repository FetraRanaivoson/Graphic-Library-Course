//
// Created by Fetra on 8/2/2021.
//

#include "GameObject.h"

GameObject::GameObject(int x, int y) {
    this->x = x;
    this->y = y;
}

void GameObject::print() {
    std::cout << this->x << " " << this->y << std::endl;
}

int GameObject::getX() const {
    return x;
}

int GameObject::getY() const {
    return y;
}

