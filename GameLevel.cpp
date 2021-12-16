#include "GameLevel.hpp"

void GameLevel::init(std::string name, Tileset *tileset)
{
    this->name = name;
    std::cout << "New level with name = " << this->name << std::endl;

    IsoTileMap map;
    IsoTileMap map2;

    std::vector<std::vector<int>> mapL = {{9, 8, 8, 8},
                                          {8, 8, 8, 8},
                                          {8, 8, 8, 8},
                                          {8, 8, 8, 8}};
    std::vector<std::vector<int>> mapL2 = {{-1, -1, -1, -1},
                                           {-1, 10, -1, -1},
                                           {-1, -1, -1, -1},
                                           {-1, -1, 10, -1}};

    map.loadTilset(4, 4, tileset, mapL);
    map2.loadTilset(4, 4, tileset, mapL2);

    tileLayers.push_back(map);
    tileLayers.push_back(map2);
}
