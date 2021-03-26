#pragma once
#include <SFML\Graphics.hpp>
#include "Grid.h"

class ResourceManager {

public:

	static void init(Grid &grid);
	static std::map<std::string, sf::Texture*> TEXTURES;
	static void load(std::string name, std::string path);

	static void saveMap( std::string fileName, Grid &grid);
	static void loadMap(std::string fileName, Grid &grid);
	static void loadMapData(std::string data, Grid &grid);
	static void clearMap(Grid &grid);
	static std::string getMapDetails(Grid &grid);

};

