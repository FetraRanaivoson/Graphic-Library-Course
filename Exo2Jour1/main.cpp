#include <iostream>
#include <map>
#include "Image.h"

bool addImage(const std::string &userInput);
bool removeImage(const std::string &userInput);
void displayImages(std::map<int, Image *> &images, std::map<int, int> &utilization);
void initializeImages(int IMAGE_INITIAL_COUNT, std::map<int, Image *> &images, std::map<int, int> &utilization);
std::string getInput();

bool exitProgram(const std::string &userInput);

int main() {
    int IMAGE_INITIAL_COUNT = 5;
    std::map<int, Image *> images;
    std::map<int, int> utilization;//first parameter is id, second is utilization number(0 by default)

    initializeImages(IMAGE_INITIAL_COUNT, images, utilization);

    bool exit = false;
    while (!exit) {
        displayImages(images, utilization);
        std::string userInput = getInput();

        if (addImage(userInput)) {
            std::cout << "Enter an Id" << std::endl;
            std::string imageId;
            std::cin >> imageId;

            if (images.contains(std::stoi(imageId))) {
                utilization.find(std::stoi(imageId))->second++;
            } else {
                Image *img = new Image(std::stoi(imageId), "img" + imageId);
                images.insert(std::pair<int, Image *>(std::stoi(imageId), img));
                utilization.insert(std::pair<int, int>(std::stoi(imageId), 0));
            }

        } else if (removeImage(userInput)) {
            std::cout << "Enter Id to remove" << std::endl;
            std::string imageId;
            std::cin >> imageId;

            if (images.contains(std::stoi(imageId))) {
                images.erase(std::stoi(imageId));
                utilization.erase(std::stoi(imageId));
            }

        }

        if (exitProgram(userInput))
            exit = true;
    }

    return 0;
}

bool exitProgram(const std::string &userInput) { return userInput == "e" || userInput == "E"; }


std::string getInput() {
    std::string userInput;
    std::cout << "Add image (A) / Remove image (R) / Exit (E) " << std::endl;
    std::cin >> userInput;
    return userInput;
}

void initializeImages(int IMAGE_INITIAL_COUNT, std::map<int, Image *> &images, std::map<int, int> &utilization) {
    for (int i = 0; i < IMAGE_INITIAL_COUNT; i++) {
        Image *img = new Image(i, "img" + std::to_string(i));
        images.insert(std::pair<int, Image *>(i, img));
        utilization.insert(std::pair<int, int>(i, 0));
    }
}

void displayImages(std::map<int, Image *> &images, std::map<int, int> &utilization) {
    for (std::pair<int, Image *> img : images) {
        std::cout << img.second->getName() << "(" << utilization.find(img.first)->second << ")" << " * ";
    }
    std::cout << std::endl;
}

bool removeImage(const std::string &userInput) { return userInput == "r" || userInput == "R"; }

bool addImage(const std::string &userInput) { return userInput == "a" || userInput == "A"; }
