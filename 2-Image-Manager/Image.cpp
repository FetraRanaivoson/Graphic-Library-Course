//
// Created by Fetra on 8/2/2021.
//

#include "Image.h"

Image::Image(int id, std::string name) {
    this->id = id;
    this->name = name;
}

const std::string &Image::getName() const {
    return name;
}
