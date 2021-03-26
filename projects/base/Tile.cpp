#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"


	Tile::Tile(int id, int startX, int startY) {
		Tile::id = id;
		x = startX;
		y = startY;

		tileShape = sf::RectangleShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		tileShape.setOutlineThickness(1);
		tileShape.setPosition(x, y);
		sprite.setScale(0.5f, 0.5f); // TEMPORARY HARD CODED - to reduce 128x128 texture to fit 64x64 tile.
		sprite.setPosition(x, y);
	}

	bool Tile::isInTile(int mouseX, int mouseY) {
		if (mouseX > x && mouseY > y 
			&& mouseX < (x + TILE_SIZE) && mouseY < (y + TILE_SIZE))
			return true;
		
		return false;
	}

	void Tile::setTexture(std::string textureName) {
		Tile::textureName = textureName;
		sf::Texture *texture = ResourceManager::TEXTURES[Tile::textureName];
		Tile::sprite.setTexture(*texture);
		showSprite = true;
	}

	void Tile::removeSprite() {
		showSprite = false;
		Tile::textureName = "";
	}

