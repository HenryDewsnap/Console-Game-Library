#include <iostream>
#include <vector>
#include <map>


class spriteManagerObject{
    private:
        std::map<std::string, std::vector<std::vector<int>>> spriteMap;

    public:
        void addSprite(std::pair<std::string, std::vector<std::vector<int>>> spriteData);

};

void spriteManagerObject::addSprite(std::pair<std::string, std::vector<std::vector<int>>> spriteData) {
    spriteMap.insert(spriteData);
}
