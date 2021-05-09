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
	}


	spriteWidth = spriteSheetTexture->getSize().x / totalFrames;
	spriteHeight = spriteSheetTexture->getSize().y / totalRows;

	spriteSheet.setTexture(*spriteSheetTexture);
	setFrame(0);

}


void AnimatedSprite::update()
{
}

void AnimatedSprite::render(sf::RenderWindow& m_window)
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

	m_window.draw(spriteSheet);
}


void AnimatedSprite::setFrame(int frame) {
	spriteSheet.setTextureRect(sf::IntRect(spriteWidth * frame, spriteHeight * currentRow, spriteWidth, spriteHeight));

}

void AnimatedSprite::play(bool loop)
{
	this->loop = loop;
	currentFrame = 0;
	playing = true;
}

