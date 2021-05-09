#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"

#define DEFAULT_TILE_SIZE 64

class Tile
{


public:
	Tile(int id = -1, float width = DEFAULT_TILE_SIZE, float height = DEFAULT_TILE_SIZE, int startX = 0, int startY = 0);

	sf::Text *tileInfo = new sf::Text();
	sf::RectangleShape tileShape;
	sf::Sprite *sprite;
	bool showSprite;
	static bool SHOW_TEXTURE_NAMES;

	AnimatedSprite animatedSprite;

	std::string textureName;

	int id;
	int startX;
	int startY;
	float width;
	float height;

	bool isInTile(int mouseX, int mouseY);
	void setTexture(std::string textureName);
	void removeSprite();
	void collide();

};

