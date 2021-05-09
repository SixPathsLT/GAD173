#include "SceneManager.h"
#include "Scenes/MenuScene.h"
#include "Scenes/GameScene.h"
#include"Scenes/LevelsScene.h"

SceneManager::SceneManager() : App()
{
}

SceneManager::~SceneManager()
{
	/*for (auto scene : scenes)
		delete scene;
	
	scenes.clear();*/
}

bool SceneManager::start()
{

	addScene(new MenuScene(&m_window));
	addScene(new LevelsScene(&m_window));
	addScene(new GameScene(&m_window));

	Scene* scene = loadScene(0);
	if (scene != nullptr)
		scene->start();
	return true;
}


void SceneManager::addScene(Scene *scene)
{
	scenes.push_back(scene);
}

void SceneManager::removeScene(int index)
{
	Scene* scene = getScene(index);
	if (scene == nullptr)
		return;

	scenes.erase(scenes.begin() + index);
}

void SceneManager::endScene(int index)
{
	Scene* scene = getScene(index);
	if (scene == nullptr)
		return;

	scene->end();
}


Scene* SceneManager::loadScene(int index)
{
	Scene* currentScene = getScene(currentSceneIndex);
	if (currentScene != nullptr)
		currentScene->end();

	Scene* scene = getScene(index);
	if (scene == nullptr)
		return nullptr;

	currentSceneIndex = index;
	scene->load();

	return scene;
}

void SceneManager::update(float deltaT)
{
	Scene* scene = getScene(currentSceneIndex);
	if (scene == nullptr)
		return;

	scene->update();
}

void SceneManager::render()
{
	Scene* scene = getScene(currentSceneIndex);
	
	if (scene == nullptr)
		return;

	scene->render();

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	sf::Text mouseInfo;
	mouseInfo.setFont(ResourceManager::FONT_BLUE_HIGH);
	mouseInfo.setString("X: " + std::to_string(mousePos.x) + "\nY: " + std::to_string(mousePos.y));
	mouseInfo.setCharacterSize(20);
	mouseInfo.setPosition(1575, 3);

	m_window.draw(mouseInfo);
}

Scene* SceneManager::getScene(int index) {
	if (index >= scenes.size())
		return nullptr;

	Scene* scene = scenes[index];
	if (scene != nullptr)
		return scene;

	return nullptr;
}