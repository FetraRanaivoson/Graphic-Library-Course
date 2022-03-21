//
// Created by Fetra on 8/2/2021.
//

#include <iostream>

class GameObject {
private:
    int x, y;

public:
    GameObject(int x, int y);

    int getX() const;
    int getY() const;

    void print();
};

