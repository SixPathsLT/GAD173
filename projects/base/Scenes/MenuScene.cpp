#include "MenuScene.h"
#include <kage2dutil/texture_manager.h>
#include <iostream>
#include "ResourceManager.h"
#include "AnimatedSprite.h"
#include "GameManager.h"

AnimatedSprite animatedSprite;

MenuScene::MenuScene(sf::RenderWindow* m_window)
{
	this->m_window = m_window;
	m_backgroundSprite = kage::TextureManager::getSprite("data/GameData/background.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window->getSize().x) / resolution.x, float(m_window->getSize().y) / resolution.y);

}

void MenuScene::load() {
	text->setString("EVIL CHOCOBO");
	text->setPosition(580, 50);
	text->setCharacterSize(150);
	sf::Color color = sf::Color::Red;
	text->setFillColor(sf::Color(color.r, color.g, color.b, 100));
	text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(5);

	Button::LOAD_BUTTON.setPosition(870, 400);
	Button::QUIT_BUTTON.setPosition(870, 500);

	animatedSprite.setAnimation(AnimatedSprite::CHOCOBO, 90);
	animatedSprite.setRow(2);
	animatedSprite.play(true);
	Button::SELECTED_BUTTON = &Button::LOAD_BUTTON;

	Scene::load();

}

bool MenuScene::start()
{
	Scene::start();
	return true;
}

void MenuScene::end() {
	Scene::end();
}

void MenuScene::update()
{
	if (!isRunning)
		return;

	if (Button::SELECTED_BUTTON != nullptr) {
		animatedSprite.spriteSheet.setPosition(Button::SELECTED_BUTTON->sprite.getPosition().x - animatedSprite.spriteWidth, Button::SELECTED_BUTTON->sprite.getPosition().y - 30);		
	}


	Button::LOAD_BUTTON.update(*m_window);
	Button::QUIT_BUTTON.update(*m_window);

	animatedSprite.update();
	Scene::update();

}

void MenuScene::render()
{
	if (!isRunning)
		return;

	m_window->draw(*m_backgroundSprite);
	Button::LOAD_BUTTON.render(*m_window);
	Button::QUIT_BUTTON.render(*m_window);

	animatedSprite.render(*m_window);

	m_window->draw(*text);
}
