#pragma once
#include "SFML/Graphics.hpp"
class Button
{


public:
	sf::Text* text = new sf::Text();
	sf::Sprite sprite;
	sf::Color color;

	Button();
	~Button();
	Button(std::string name, std::string textureName, sf::Color color, float scale = 1.0f, int textSize = 40);
	void setText(std::string name);

	static Button* SELECTED_BUTTON;

	static Button START_BUTTON;
	static Button LOAD_BUTTON;
	static Button PAUSE_BUTTON;
	static Button MENU_BUTTON;
	static Button QUIT_BUTTON;

	static void init();
	static void processClick(sf::RenderWindow &m_window);

	void setPosition(int x, int y);
	void update(sf::RenderWindow &m_window);
	void render(sf::RenderWindow &m_window);

};

