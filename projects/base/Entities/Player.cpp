#include "Player.h"
#include <GameManager.h>
#include <Utils.h>

Player::Player(float health, int speed) : Entity(health, speed)
{
	playerShape = sf::RectangleShape(sf::Vector2f(100, 15));

	playerShape.setOutlineColor(sf::Color::White);
	playerShape.setOutlineThickness(3);
	setPosition(900, 900);
}

void Player::setFillColor(sf::Color color)
{
	playerShape.setOutlineColor(color);
	playerShape.setFillColor(color);
}

void Player::setPosition(int x, int y)
{
	int offset = 8;

	if (x - offset <= GameManager::grid.rectShape.getGlobalBounds().left)
		x = (GameManager::grid.rectShape.getGlobalBounds().left) + offset;
	else if((playerShape.getSize().x) + x + offset >= (GameManager::grid.rectShape.getGlobalBounds().left + GameManager::grid.rectShape.getGlobalBounds().width))
		x = (GameManager::grid.rectShape.getGlobalBounds().left + GameManager::grid.rectShape.getGlobalBounds().width) - (playerShape.getSize().x + offset);

	Entity::setPosition(x, y);
	healthBar.setPosition(x, y);
	playerShape.setPosition(x, y);

}

void Player::update(sf::RenderWindow &m_window)
{
	Entity::update(m_window);

	if (playerShape.getOutlineColor() == sf::Color::White)
		clock.restart();

	if (clock.getElapsedTime().asMilliseconds() > 600) {
		setFillColor(sf::Color::White);
		clock.restart();
	}


		sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

		Tile startTile = GameManager::grid.tiles[0];
		Tile endTile = GameManager::grid.tiles[GameManager::grid.getSize() - 1];

		int x = mousePos.x - (playerShape.getSize().x / 2);

		setPosition(x, playerShape.getPosition().y);
	
}

void Player::render(sf::RenderWindow & m_window)
{
	m_window.draw(playerShape);
	Entity::render(m_window);

}
