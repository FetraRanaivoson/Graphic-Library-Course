//
// Created by Fetra on 8/2/2021.
//

#include <string>

#ifndef EXO2JOUR1_IMAGE_H
#define EXO2JOUR1_IMAGE_H


class Image {
private:
    int id;
    std::string name;

public:
    Image(int id, std::string name);

    const std::string &getName() const;
};


#endif //EXO2JOUR1_IMAGE_H
