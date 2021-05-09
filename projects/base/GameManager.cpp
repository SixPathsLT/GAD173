#include "GameManager.h"

Player* GameManager::player;
Ball* GameManager::ball;

int GameManager::points = 0;
int GameManager::currentLevel = 0;
SceneManager GameManager::sceneManager;
Grid GameManager::grid;

GameManager::GameManager()
{
}

GameManager& GameManager::inst()
{
	static GameManager gameManager;
	return gameManager;
}



void GameManager::init()
{
	sceneManager.run();
}

void GameManager::openLevels()
{
	sceneManager.loadScene(1);
}

void GameManager::loadLevel(std::string name)
{

	if (name.find("CURRENT") != -1)
		name = std::to_string(currentLevel);
	else {
		name = name.substr(1 + name.find(" "));
		currentLevel = std::stoi(name);
	}

	//creates desirable grid (rows, columns, start loc X, start loc Y)
	grid = Grid(10, 15, MAP_GRID_START_X, MAP_GRID_START_Y);
	//creates desired tile dimensions (sizeX, sizeY, spacing)
	grid.createTiles(100, 45);
	player = new Player(100, 1);
	ball = new Ball();

	sceneManager.loadScene(2);

	ResourceManager::loadMap("custom_map_" + name);

}

void GameManager::startGame()
{
	Scene* scene = sceneManager.getScene(sceneManager.currentSceneIndex);
	if (scene != nullptr) {
		player = new Player(100, 1);
		ball = new Ball();

		scene->start();
	}
}

void GameManager::endGame()
{
	points = 0;
	Button::SELECTED_BUTTON = nullptr;
	sceneManager.endScene(2);

	(*sceneManager.loadScene(0)).start();
}