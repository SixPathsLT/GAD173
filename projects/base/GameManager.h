#pragma once
#include "Grid.h"
#include "SceneManager.h"
#include "Entities/Player.h"
#include "Entities/Ball.h"

class GameManager
{

public:
	static Player* player;
	static Ball* ball;
	static int points;
	static int currentLevel;
	static SceneManager sceneManager;
	static Grid grid;

	GameManager();
	void init();
	static GameManager& inst();
	static void loadLevel(std::string name = "CURRENT");
	static void openLevels();
	static void startGame();
	static void endGame();

	


};

