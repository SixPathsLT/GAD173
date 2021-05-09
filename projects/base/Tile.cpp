#include "Tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"


	Tile::Tile(int id, float width, float height, int startX, int startY) {
		this->id = id;
		this->width = width;
		this->height = height;
		this->startX = startX;
		this->startY = startY;
		
	}

	Tile::~Tile()
	{
		//delete sprite;
	}

	bool Tile::isInTile(int mouseX, int mouseY) {
		if (mouseX > startX && mouseY > startY
			&& mouseX < (startX + width) && mouseY < (startY + height))
			return true;
		
		return false;
	}

	void Tile::setTexture(std::string textureName) {
		this->textureName = textureName;

		sf::Texture *texture = ResourceManager::TEXTURES[this->textureName];
		if (texture == nullptr)
			return;

		sprite = new sf::Sprite();
		sprite->setTexture(*texture);
		sprite->setPosition(startX, startY);

		//if (texture->getSize().x > width || texture->getSize().y > height) //if our texture is bigger than the tile size, then resize texture to fit it in tile
			sprite->setScale(width / texture->getSize().x, height / texture->getSize().y);

		showSprite = true;

		sf::Color color = sprite->getTexture()->copyToImage().getPixel(sprite->getTexture()->getSize().x / 2, sprite->getTexture()->getSize().y / 2);

		animatedSprite.spriteSheet.setColor(color);

		animatedSprite.spriteSheet.setPosition(startX, startY);
		animatedSprite.setAnimation(AnimatedSprite::BLOCK, 20);
	}

	void Tile::collide() {
		if (!showSprite)
			return;


		animatedSprite.spriteSheet.setScale(width / animatedSprite.spriteWidth, height / animatedSprite.spriteHeight);

		animatedSprite.play(false);
		removeSprite();
	}

	void Tile::removeSprite() {
		showSprite = false;
		textureName = "";
	}

