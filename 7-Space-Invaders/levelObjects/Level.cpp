//
// Created by Fetra on 8/7/2021.
//

#include "Level.h"

Level::Level(const std::vector<int> &numbers)
        : numbers(numbers) {}

Level::Level(int columnCount) {

    for (int i = 0; i < columnCount; i++) {
        numbers.push_back(rand() % 2);
    }

}

int Level::getNumber(int index) {
    return numbers[index];
}

void Level::setNumbers(const std::vector<int> &numbers) {
    Level::numbers = numbers;
}

void Level::print() {
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}