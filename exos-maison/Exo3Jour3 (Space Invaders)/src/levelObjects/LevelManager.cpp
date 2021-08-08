//
// Created by Fetra on 8/7/2021.
//

#include "LevelManager.h"

LevelManager::LevelManager(int windowWidth, int windowHeight, int squareWidth, int squareHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->squareWidth = squareWidth;
    this->squareHeight = squareHeight;
}

void LevelManager::saveRandomBinaryNumbers(int columnCount, int rowCount) {
    //Prepare file for saving
    std::ofstream savedNumbers("./assets/binary.txt", std::ios::app);

    //Setup seeds
    srand((unsigned int) time(NULL));

    //Initialize allRows of numbers
    std::vector<Level *> allRows(rowCount);

    //Populate columns and rows
    for (Level *numbersPerRow : allRows) {
        numbersPerRow = new Level(columnCount);
        //Save them to file
        for (int i = 0; i < columnCount; i++) {
            if (i < columnCount - 1)
                savedNumbers << numbersPerRow->getNumber(i) << " ";
            if (i == columnCount - 1)
                savedNumbers << numbersPerRow->getNumber(i) << " " << std::endl;
        }
    }


}

void LevelManager::loadRandomBinaryNumbers(int columnCount, std::vector<Level*> &retrievedNumbers) {

    std::string retrievedFile = "./assets/binary.txt";
    std::ifstream filesIn(retrievedFile.c_str());

    if (filesIn) {
        std::vector<int> inlineWords;
        std::string word;

        while (filesIn >> word) {
            inlineWords.push_back(std::stoi(word));
            if (inlineWords.size() == columnCount) {
                retrievedNumbers.push_back(new Level(inlineWords));
                inlineWords.clear();
            }
        }
    }
}

int LevelManager::getColumnCount() {

    //w * col = W
    //col = W /w;

    return windowWidth / squareWidth;
}

int LevelManager::getRowCount() {

    //h * row = H
    //row = H/h
    return windowHeight / squareHeight;
}

LevelManager::LevelManager() {

}
