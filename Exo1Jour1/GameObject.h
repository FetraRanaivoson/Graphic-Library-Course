//
// Created by Fetra on 8/2/2021.
//

#include <iostream>

#ifndef EXO1JOUR1_GAMEOBJECT_H
#define EXO1JOUR1_GAMEOBJECT_H


class GameObject {
private:
    int x, y;

public:
    GameObject(int x, int y);

    int getX() const;
    int getY() const;

    void print();
};


#endif //EXO1JOUR1_GAMEOBJECT_H
