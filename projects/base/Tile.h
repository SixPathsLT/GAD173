#pragma once
#include <SFML/Graphics.hpp>

#define TILE_SIZE 64

class Tile
{


public:
	Tile(int id = -1, int startX = 0, int startY = 0);

	sf::RectangleShape tileShape;
	sf::Sprite sprite;
	bool showSprite;

	std::string textureName;

	int id;
	int x;
	int y;

	bool isInTile(int mouseX, int mouseY);
	void setTexture(std::string textureName);
	void removeSprite();

};

