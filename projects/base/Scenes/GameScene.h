#pragma once
#include "Scene.h"
#include "Grid.h"
#include "Entities/Ball.h"
#define TOTAL_COINS 5

class GameScene : public Scene
{

private:
	AnimatedSprite* animatedCoins;
	Ball* balls;
	sf::Clock clock;
	sf::Text* scoreText = new sf::Text();

public:
	GameScene(sf::RenderWindow* m_window = nullptr);
	~GameScene();


	bool start() override;
	void load() override;
	void end() override;
	void update();
	void render() override;

	bool gameOver();

};

