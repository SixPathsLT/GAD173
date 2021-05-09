#include "AnimatedSprite.h"
#include "ResourceManager.h"
#include "SFML/Graphics.hpp"
#include <iostream>


AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::setAnimation(SpriteType spriteType, int speed) {
	this->speed = speed;

	switch (spriteType)
	{
	case AnimatedSprite::BLOCK:
		spriteSheetTexture = ResourceManager::TEXTURES["block_spritesheet"];
		totalFrames = 10;
		totalRows = 1;
		break;
	case AnimatedSprite::COIN:
		spriteSheetTexture = ResourceManager::TEXTURES["coin_spritesheet"];
		totalFrames = 6;
		totalRows = 1;
		break;
	case AnimatedSprite::CHOCOBO:
		spriteSheetTexture = ResourceManager::TEXTURES["chocobo_spritesheet"];
		totalFrames = 4;
		totalRows = 4;
		spriteWidth = 1;
		spriteHeight = -1;
		break;
	case AnimatedSprite::FIRE_EFFECT:
		spriteSheetTexture = ResourceManager::TEXTURES["fire_effect_spritesheet"];
		totalFrames = 9;
		totalRows = 1;
		break;
	case AnimatedSprite::EXPLOSION_EFFECT:
		spriteSheetTexture = ResourceManager::TEXTURES["explosion_spritesheet"];
		totalFrames = 7;
		totalRows = 1;
		break;
	}


	spriteWidth += (spriteSheetTexture->getSize().x / totalFrames);
	spriteHeight += (spriteSheetTexture->getSize().y / totalRows);

	spriteSheet.setTexture(*spriteSheetTexture);
	setFrame(0);

}


void AnimatedSprite::update()
{
	if (!playing)
		return;

	if (clock.getElapsedTime().asMilliseconds() > speed) {
		setFrame(currentFrame);

		currentFrame++;
		if (currentFrame >= totalFrames) {
			currentFrame = 0;

			if (!loop)
				playing = false;
		}

		if (currentRow > totalRows)
			currentRow = 1;

		clock.restart();
	}
}

void AnimatedSprite::render(sf::RenderWindow& m_window)
{
	if (!playing)
		return;

	m_window.draw(spriteSheet);
}


void AnimatedSprite::setFrame(int frame) {
	spriteSheet.setTextureRect(sf::IntRect(spriteWidth * frame, spriteHeight * currentRow, spriteWidth, spriteHeight));

}

void AnimatedSprite::setRow(int row) {
	currentRow = row;
}

void AnimatedSprite::play(bool loop)
{
	this->loop = loop;
	currentFrame = 0;
	playing = true;
}

