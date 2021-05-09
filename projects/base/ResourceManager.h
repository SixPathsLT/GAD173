#pragma once
#include <SFML\Graphics.hpp>
#include "Grid.h"

class ResourceManager {
	
public:
	static sf::Font FONT_BLUE_HIGH;
	static std::map<std::string, sf::Texture*> TEXTURES;
	~ResourceManager();
	static void init();
	static void loadMap(std::string fileName);
	static void loadMapData(std::string data);
	static void clearMap();
	


};

