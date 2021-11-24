#include "GameLevel.hpp"

void GameLevel::init(std::string name, Tileset *tileset)
{
    this->name = name;
    std::cout << "New level with name = " << this->name << std::endl;

    IsoTileMap map;
    IsoTileMap map2;

    std::vector<std::vector<int>> mapL = {{2, 1, 1, 1},
                                          {1, 0, 0, 1},
                                          {1, 0, 0, 1},
                                          {1, 1, 1, 2}};
    std::vector<std::vector<int>> mapL2 = {{-1, -1, -1, -1},
                                           {3, -1, -1, -1},
                                           {3, -1, -1, -1},
                                           {4, 5, 5, -1}};

    map.loadTilset(4, 4, tileset, mapL);
    map2.loadTilset(4, 4, tileset, mapL2);

    tileLayers.push_back(map);
    tileLayers.push_back(map2);
}
