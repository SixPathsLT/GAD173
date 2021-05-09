#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"

class Scene
{

protected:
	sf::Sprite *m_backgroundSprite;
	sf::RenderWindow* m_window;
	sf::Text* text = new sf::Text();

public:
	bool isRunning = false;

	Scene();
	~Scene();

	virtual bool start();
	virtual void load();
	virtual void end();
	virtual void update();
	virtual void render();
};

