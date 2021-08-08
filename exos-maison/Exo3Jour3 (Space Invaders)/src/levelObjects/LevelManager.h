//
// Created by Fetra on 8/7/2021.
//

#ifndef SPACEINVADERS_LEVELMANAGER_H
#define SPACEINVADERS_LEVELMANAGER_H

#include <vector>
#include <fstream>
#include "Level.h"


class LevelManager {
private:
    int windowWidth, windowHeight, squareWidth, squareHeight;

public:
    LevelManager();
    LevelManager(int windowWidth, int windowHeight, int squareWidth, int squareHeight);

    void saveRandomBinaryNumbers(int columnCount, int rowCount);

    void loadRandomBinaryNumbers(int columnCount, std::vector<Level*> &retrievedNumbers);

    int getColumnCount();
    int getRowCount();

};


#endif //SPACEINVADERS_LEVELMANAGER_H
