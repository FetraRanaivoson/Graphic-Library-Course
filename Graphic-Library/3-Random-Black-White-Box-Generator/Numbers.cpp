//
// Created by Fetra on 8/3/2021.
//

#include "Numbers.h"

Numbers::Numbers(int columnCount) {

    for (int i = 0; i < columnCount; i++) {
        numbers.push_back(rand()%2);
    }

}

int Numbers::getNumber(int index) {
    return numbers[index];
}

void Numbers::setNumbers(const std::vector<int> &numbers) {
    Numbers::numbers = numbers;
}

Numbers::Numbers(const std::vector<int> &numbers)
    : numbers(numbers)
{}

void Numbers::print() {
    for (int i =0; i< numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
}



