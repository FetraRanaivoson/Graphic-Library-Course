#include <iostream>
#include "GameObject.h"
#include <vector>
#include <fstream>
#include <string>

void saveGameObjects();

void loadGameObjects(std::vector<GameObject *> &retrievedGameObjects);

bool endLine(const std::vector<std::string> &inlineWords);

void onExistingSaved(std::vector<GameObject *> &retrievedGameObjects, std::ifstream &filesIn);

void printGameObjects(std::vector<GameObject *> &retrievedGameObjects);

int main() {
    saveGameObjects();

    std::vector<GameObject*> retrievedGameObjects;

    loadGameObjects(retrievedGameObjects);
    printGameObjects(retrievedGameObjects);

    return 0;
}

void printGameObjects(std::vector<GameObject *> &retrievedGameObjects) {
    if (!retrievedGameObjects.empty()) {
        for (GameObject* retrieved : retrievedGameObjects) {
            retrieved->print();
        }
    } else {
        std::cout << "No game saved." << std::endl;
    }
}

void loadGameObjects(std::vector<GameObject *> &retrievedGameObjects) {
    //Prepare saved file
    std::string retrievedFile = "./sav.game";
    std::ifstream filesIn(retrievedFile.c_str());

    if (filesIn) {
        onExistingSaved(retrievedGameObjects, filesIn);
    }
}

void onExistingSaved(std::vector<GameObject *> &retrievedGameObjects, std::ifstream &filesIn) {
    std::vector<std::string> inlineWords;
    std::string word;

    //Read word by word
    while (filesIn >> word) {
        inlineWords.push_back(word);
        if (endLine(inlineWords)) {
            retrievedGameObjects.push_back(new GameObject(std::stoi(inlineWords[0]), std::stoi(inlineWords[1])));
            inlineWords.clear();
        }
    }
}

bool endLine(const std::vector<std::string> &inlineWords)
{
    return inlineWords.size() == 2;
}

void saveGameObjects() {
    //Prepare file for saving games
    std::ofstream savedGame("./sav.game", std::ios::app);

    //Setup seeds
    srand((unsigned int) time(NULL));

    //Initialize objects and save them to file
    std::vector<GameObject *> objects(10);
    for (GameObject *go : objects) {
        go = new GameObject(rand() % 100, rand() % 100);
        savedGame << go->getX() << " " << go->getY() << std::endl;
    }
}
