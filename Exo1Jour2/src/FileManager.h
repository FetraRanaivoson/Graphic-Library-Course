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

public:
    FileManager();

    void saveRandomBinaryNumbers(int columnCount, int rowCount);

    void loadRandomBinaryNumbers(int columnCount, std::vector<Numbers*> &retrievedNumbers);

};


#endif //EXO1JOUR2_FILEMANAGER_H
