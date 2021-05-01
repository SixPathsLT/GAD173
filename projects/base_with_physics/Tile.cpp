#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"


	bool Tile::SHOW_TEXTURE_NAMES = false;

	Tile::Tile(int id, float width, float height, int startX, int startY) {
		this->id = id;
		this->width = width;
		this->height = height;
		this->startX = startX;
		this->startY = startY;

		tileShape = sf::RectangleShape(sf::Vector2f(width, height));
		tileShape.setOutlineThickness(1);
		tileShape.setPosition(this->startX, this->startY);

		tileInfo->setFont(ResourceManager::FONT_BLUE_HIGH);
		tileInfo->setString(textureName);
		tileInfo->setCharacterSize(15);
	}

	bool Tile::isInTile(int mouseX, int mouseY) {
		if (mouseX > startX && mouseY > startY
			&& mouseX < (startX + width) && mouseY < (startY + height))
			return true;
		
		return false;
	}

	void Tile::setTexture(std::string textureName) {
		this->textureName = textureName;
		tileInfo->setString(this->textureName);

		int posX = startX + (tileShape.getSize().x / 2) - (tileInfo->getFont()->getInfo().family.size() + (tileInfo->getString().getSize() * 2));
		int posY = startY + (tileShape.getSize().y / 2) - tileInfo->getFont()->getInfo().family.size();
		tileInfo->setPosition(posX, posY);

		sf::Texture *texture = ResourceManager::TEXTURES[this->textureName];
		if (texture == nullptr)
			return;

		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		sprite->setPosition(startX, startY);

		//if (texture->getSize().x > width || texture->getSize().y > height) //if our texture is bigger than the tile size, then resize texture to fit it in tile
			sprite->setScale(width / texture->getSize().x, height / texture->getSize().y);

		showSprite = true;
	}

	void Tile::removeSprite() {
		showSprite = false;
		textureName = "";
		tileInfo->setString(textureName);
	}

