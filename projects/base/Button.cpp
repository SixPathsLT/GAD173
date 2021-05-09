#include "Button.h"
#include "ResourceManager.h"
#include <iostream>
#include "Utils.h"
#include "GameManager.h"

Button* Button::SELECTED_BUTTON;

Button Button::START_BUTTON;
Button Button::LOAD_BUTTON;
Button Button::PAUSE_BUTTON;
Button Button::MENU_BUTTON;
Button Button::QUIT_BUTTON;

Button::Button()
{
}

Button::~Button()
{
	//delete text;
}

Button::Button(std::string name, std::string textureName, sf::Color color, float scale, int textSize)
{
	this->color = color;

	sprite.setTexture(*ResourceManager::TEXTURES[textureName]);
	sprite.setScale(scale, scale);
	sprite.setColor(color);

	text->setFont(ResourceManager::FONT_BLUE_HIGH);
	text->setCharacterSize(textSize);
	
	setText(name);
}

void Button::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
	setText(text->getString());
}


void Button::setText(std::string name) {
	text->setString(name);
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
	text->setPosition(sf::Vector2f(sprite.getPosition().x + (sprite.getGlobalBounds().width / 2), sprite.getPosition().y + (sprite.getGlobalBounds().height / 2)));
}

void Button::init()
{
	START_BUTTON = Button("RETRY", "button", sf::Color::Cyan, 0.55, 100);
	LOAD_BUTTON = Button("PLAY", "button", sf::Color::Cyan, 0.25);
	QUIT_BUTTON = Button("QUIT", "button", sf::Color::Red, 0.25);
	PAUSE_BUTTON = Button("PAUSE", "button", sf::Color::Cyan, 0.25);
	MENU_BUTTON = Button("MENU", "button", sf::Color::Yellow, 0.25);
}


void Button::processClick(sf::RenderWindow &m_window)
{
	if (SELECTED_BUTTON == nullptr)
		return;

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	std::string name = SELECTED_BUTTON->text->getString();
	
	if (Utils::collides(mousePos.x, mousePos.y, SELECTED_BUTTON->sprite.getGlobalBounds())) {
		if (SELECTED_BUTTON->text->getString().find("LEVEL") != -1) {
			std::string name = SELECTED_BUTTON->text->getString();

			GameManager::loadLevel(name);
		} else if (SELECTED_BUTTON == &START_BUTTON)
			GameManager::loadLevel();
		else if (SELECTED_BUTTON == &MENU_BUTTON) {
			GameManager::endGame();
		} else if (SELECTED_BUTTON == &PAUSE_BUTTON) {
			Scene* scene = GameManager::sceneManager.getScene(GameManager::sceneManager.currentSceneIndex);
			if (scene == nullptr)
				return;

			scene->isRunning = !scene->isRunning;
			PAUSE_BUTTON.setText(scene->isRunning ? "PAUSE" : "RESUME");
		} else if (SELECTED_BUTTON == &LOAD_BUTTON) {
			GameManager::openLevels();
		} else if (SELECTED_BUTTON == &QUIT_BUTTON) {
			m_window.close();
		}
	}

	SELECTED_BUTTON = nullptr;
}



void Button::update(sf::RenderWindow &m_window)
{
		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
		
		if (Utils::collides(mousePos.x, mousePos.y, sprite.getGlobalBounds())) {
			sprite.setColor(sf::Color(color.r, color.g, color.b, 255));
			SELECTED_BUTTON = this;
		} else {
			sprite.setColor(sf::Color(color.r, color.g, color.b, 200));
		}
	

}

void Button::render(sf::RenderWindow &m_window)
{
	m_window.draw(sprite);
	m_window.draw(*text);
}
