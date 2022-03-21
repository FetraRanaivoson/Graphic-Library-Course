//
// Created by Fetra on 8/2/2021.
//

#include <string>
class Image {
private:
    int id;
    std::string name;

public:
    Image(int id, std::string name);

    const std::string &getName() const;
};

