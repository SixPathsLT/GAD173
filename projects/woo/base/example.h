#pragma once

#include "app.h"
#include "Grid.h";
#include "AnimatedSprite.h"

class Example : public App
{
public:
	Example();
	virtual ~Example();
	virtual bool start();
	virtual void update(float deltaT);
	virtual void render();
	virtual void cleanup();
	static Example &inst();

	sf::Sprite *m_backgroundSprite;

	Grid mapGrid;

	bool fileExists = false;


	enum ToolTab {
		NONE,
		CLEAR_MAP,
		DRAW,
		SETTINGS,
		INFO
	};

	ToolTab selectedTab;


};
