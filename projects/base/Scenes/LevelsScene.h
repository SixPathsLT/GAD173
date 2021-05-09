#pragma once
#include "Scene.h"
#include "Button.h"

class LevelsScene : public Scene
{

private:
	std::vector<Button*> buttons;

public:
	LevelsScene(sf::RenderWindow* m_window = nullptr);
	~LevelsScene();

	bool start() override;
	void load() override;
	void end() override;
	void update() override;
	void render() override;
};