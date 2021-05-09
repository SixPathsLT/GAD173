#include "Scene.h"
#include <iostream>
#include "ResourceManager.h"
Scene::Scene()
{
	text->setFont(ResourceManager::FONT_BLUE_HIGH);
	text->setCharacterSize(40);
}

Scene::~Scene()
{
	/*delete m_backgroundSprite;
	delete m_window;
	delete text;*/
}


bool Scene::start()
{
	isRunning = true;
	return isRunning;
}

void Scene::load()
{

	isRunning = true;
}

void Scene::end()
{

	isRunning = false;
}

void Scene::update()
{


}

void Scene::render() {

}