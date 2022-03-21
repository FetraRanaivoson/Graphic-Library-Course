//
// Created by Fetra on 8/7/2021.
//

#include <vector>
#include <string>
#include <fstream>
#include "Level.h"


class LevelManager {
private:
    int windowWidth, windowHeight, squareWidth, squareHeight;

public:
    LevelManager();
    LevelManager(int windowWidth, int windowHeight, int squareWidth, int squareHeight);

    void saveRandomNumbers(int columnCount, int rowCount);

    void loadRandomNumbers(int columnCount, std::vector<Level*> &retrievedNumbers);

    int getColumnCount();
    int getRowCount();

};

