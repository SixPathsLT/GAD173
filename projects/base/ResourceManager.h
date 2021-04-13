#pragma once
#include <SFML\Graphics.hpp>
#include "Grid.h"

class ResourceManager {
	
public:
	static int TOTAL_LOADED_TEXTURES;

	static sf::Texture *selectedTexture;
	static sf::Font FONT_BLUE_HIGH;

	static char fileName[26];

	static void init();

	static std::map<std::string, sf::Texture*> TEXTURES;

	static void saveMap(Grid &grid);
	static void loadMap(Grid &grid);
	static void loadMapData(std::string data, Grid &grid);
	static void clearMap(Grid &grid);
	static std::string getMapDetails(Grid &grid);

	static std::string getKey(sf::Texture *texture);

	static int getTotalLoadedTextures();

};

