//
// Created by Fetra on 8/3/2021.
//
#include <vector>
#include <iostream>


class Numbers {
private:
    std::vector <int> numbers;

public:
    Numbers(int columnCount);
    Numbers(const std::vector<int> &numbers);

    int getNumber(int index);
    void setNumbers(const std::vector<int> &numbers);

    void print();

};
