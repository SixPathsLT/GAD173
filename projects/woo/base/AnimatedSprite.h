#pragma once
#include "SFML/Graphics.hpp"


class AnimatedSprite
{

public: static const enum SpriteType {
		BLOCK,
		COIN
	};

private:
	int totalFrames = 1;
	int totalRows = 1;

	int speed = 0;
	int currentFrame = 0;
	int currentRow = 0;

	bool playing = false;
	bool loop = false;

	SpriteType spriteType;

	sf::Clock clock;

public:
	AnimatedSprite();
	~AnimatedSprite();
	int spriteWidth = 0;
	int spriteHeight = 0;
	sf::Sprite spriteSheet;
	sf::Texture* spriteSheetTexture = nullptr;

	void setAnimation(SpriteType spriteType, int speed);

	void update();
	void render(sf::RenderWindow& m_window);

	void setFrame(int frame);
	void play(bool loop);

};

