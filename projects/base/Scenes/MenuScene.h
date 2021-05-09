#pragma once
#include "Scene.h"

class MenuScene : public Scene
{

public:
	MenuScene(sf::RenderWindow* m_window = nullptr);
	~MenuScene();

	bool start() override;
	void load() override;
	void end() override;
	void update() override;
	void render() override;

};

