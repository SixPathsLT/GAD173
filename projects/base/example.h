#pragma once

#include "app.h"
#include "Grid.h";

class Example : public App
{
public:
	Example();
	virtual ~Example();
	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();
	virtual void processMouseClick(sf::Vector2i mousePos);
	virtual void cleanup();
	static Example &inst();

	sf::Sprite *m_backgroundSprite;

	Grid mapGrid;
	Grid toolGrid;

};
