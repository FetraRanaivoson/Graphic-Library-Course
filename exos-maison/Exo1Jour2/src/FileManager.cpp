//
// Created by Fetra on 8/3/2021.
//

#include "FileManager.h"


FileManager::FileManager(int windowWidth, int windowHeight, int squareWidth, int squareHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->squareWidth = squareWidth;
    this->squareHeight = squareHeight;
}

void FileManager::saveRandomBinaryNumbers(int columnCount, int rowCount) {
    //Prepare file for saving
    std::ofstream savedNumbers("./assets/binary.txt", std::ios::app);

    //Setup seeds
    srand((unsigned int) time(NULL));

    //Initialize allRows of numbers
    std::vector<Numbers *> allRows(rowCount);

    //Populate columns and rows
    for (Numbers *numbersPerRow : allRows) {
        numbersPerRow = new Numbers(columnCount);
        //Save them to file
        for (int i = 0; i < columnCount; i++) {
            if (i < columnCount - 1)
                savedNumbers << numbersPerRow->getNumber(i) << " ";
            if (i == columnCount - 1)
                savedNumbers << numbersPerRow->getNumber(i) << " " << std::endl;
        }
    }


}

void FileManager::loadRandomBinaryNumbers(int columnCount, std::vector<Numbers*> &retrievedNumbers) {

    std::string retrievedFile = "./assets/binary.txt";
    std::ifstream filesIn(retrievedFile.c_str());

    if (filesIn) {
        std::vector<int> inlineWords;
        std::string word;

        while (filesIn >> word) {
            inlineWords.push_back(std::stoi(word));
            if (inlineWords.size() == columnCount) {
                retrievedNumbers.push_back(new Numbers(inlineWords));
                inlineWords.clear();
            }
        }


    }


}

int FileManager::getColumnCount() {

    //w * col = W
    //col = W /w;

    return windowWidth / squareWidth;
}

int FileManager::getRowCount() {

    //h * row = H
    //row = H/h
    return windowHeight / squareHeight;
}

FileManager::FileManager() {

}
