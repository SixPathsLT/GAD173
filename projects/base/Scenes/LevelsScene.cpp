#include "LevelsScene.h"
#include <kage2dutil/texture_manager.h>
#include "ResourceManager.h"
#include "Button.h"


LevelsScene::LevelsScene(sf::RenderWindow *m_window)
{
	this->m_window = m_window;
	m_backgroundSprite = kage::TextureManager::getSprite("data/GameData/background.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window->getSize().x) / resolution.x, float(m_window->getSize().y) / resolution.y);

	float scale = 0.5f;
	int textSize = 80;
						
	buttons.push_back(new Button("LEVEL 1", "map_1", sf::Color::White, scale, textSize));
	buttons.push_back(new Button("LEVEL 2", "map_2", sf::Color::White, scale, textSize));
	buttons.push_back(new Button("LEVEL 3", "map_3", sf::Color::White, scale, textSize));
	buttons.push_back(new Button("LEVEL 4", "map_4", sf::Color::White, scale, textSize));

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->text->setOutlineColor(sf::Color::Black);
		buttons[i]->text->setOutlineThickness(5);
	}

	int startX = 170;
	int startY = 240;
	int spacing = 50;

	int width = buttons[0]->sprite.getGlobalBounds().width;
	int height = buttons[0]->sprite.getGlobalBounds().height;

	buttons[0]->setPosition(startX, startY);
	buttons[1]->setPosition((startX + width + spacing), startY);
	buttons[2]->setPosition(startX, (startY + height + spacing));
	buttons[3]->setPosition((startX + width + spacing), (startY + height + spacing));
	
}

LevelsScene::~LevelsScene()
{
	/*for (auto button : buttons)
		delete button;

	buttons.clear();*/
}

bool LevelsScene::start()
{
	Scene::start();
	return true;
}

void LevelsScene::load()
{
	text->setString("Level Selector");
	text->setPosition(600, 0);
	text->setCharacterSize(150);

	sf::Color color = sf::Color::Green;
	text->setFillColor(sf::Color(color.r, color.g, color.b, 100));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(4);

	Button::MENU_BUTTON.setPosition(790, 820);
	Button::QUIT_BUTTON.setPosition(980, 820);

	Scene::load();
}

void LevelsScene::end()
{
	Scene::end();
}

void LevelsScene::update()
{
	if (!isRunning)
		return;

	Button::MENU_BUTTON.update(*m_window);
	Button::QUIT_BUTTON.update(*m_window);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->update(*m_window);
	}

	Scene::update();
}

void LevelsScene::render()
{
	if (!isRunning)
		return;

	m_window->draw(*m_backgroundSprite);

	Button::MENU_BUTTON.render(*m_window);
	Button::QUIT_BUTTON.render(*m_window);

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->render(*m_window);
	}


	m_window->draw(*text);
}
