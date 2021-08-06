//
// Created by Fetra on 8/3/2021.
//

#ifndef EXO1JOUR2_FILEMANAGER_H
#define EXO1JOUR2_FILEMANAGER_H
#include <vector>
#include <fstream>
#include "Numbers.h"

class FileManager {
private:
    int windowWidth, windowHeight, squareWidth, squareHeight;

public:
    FileManager();
    FileManager(int windowWidth, int windowHeight, int squareWidth, int squareHeight);

    void saveRandomBinaryNumbers(int columnCount, int rowCount);

    void loadRandomBinaryNumbers(int columnCount, std::vector<Numbers*> &retrievedNumbers);

    int getColumnCount();
    int getRowCount();
};


#endif //EXO1JOUR2_FILEMANAGER_H
