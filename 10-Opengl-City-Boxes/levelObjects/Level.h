//
// Created by Fetra on 8/7/2021.
//

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

