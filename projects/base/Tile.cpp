#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"


	bool Tile::showTextureNames = false;

	Tile::Tile(int id, float width, float height, int startX, int startY) {
		Tile::id = id;
		Tile::width = width;
		Tile::height = height;
		Tile::startX = startX;
		Tile::startY = startY;

		tileShape = sf::RectangleShape(sf::Vector2f(width, height));
		tileShape.setOutlineThickness(1);
		tileShape.setPosition(Tile::startX, Tile::startY);


		tileInfo->setFont(ResourceManager::FONT_BLUE_HIGH);
		tileInfo->setString(textureName);
		tileInfo->setCharacterSize(15);

		//tileInfo->setPosition( 15 + startX, startY + (height / 3));
	}

	bool Tile::isInTile(int mouseX, int mouseY) {
		if (mouseX > startX && mouseY > startY
			&& mouseX < (startX + width) && mouseY < (startY + height))
			return true;
		
		return false;
	}

	void Tile::setTexture(std::string textureName) {
		Tile::textureName = textureName;
		tileInfo->setString(Tile::textureName);

		int posX = startX + (tileShape.getSize().x / 2) - (tileInfo->getFont()->getInfo().family.size() + (tileInfo->getString().getSize() * 2));
		int posY = startY + (tileShape.getSize().y / 2) - tileInfo->getFont()->getInfo().family.size();
		tileInfo->setPosition(posX, posY);

		sf::Texture *texture = ResourceManager::TEXTURES[Tile::textureName];
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
		Tile::textureName = "";
		tileInfo->setString(textureName);
	}

