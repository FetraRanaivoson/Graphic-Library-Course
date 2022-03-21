//
// Created by Fetra on 8/7/2021.
//

#ifndef SPACEINVADERS_LEVEL_H
#define SPACEINVADERS_LEVEL_H
#include <vector>
#include <iostream>

class Level {
private:
    std::vector <int> numbers;

public:
    Level(int columnCount);
    Level(const std::vector<int> &numbers);

    int getNumber(int index);
    void setNumbers(const std::vector<int> &numbers);

    void print();

};

#endif //SPACEINVADERS_LEVEL_H
