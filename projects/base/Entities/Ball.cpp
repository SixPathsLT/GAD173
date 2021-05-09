#include "Ball.h"
#include "GameManager.h"
#include "Utils.h"

Ball::Ball(float health, int speed) : Entity(health, speed)
{
	ballShape = sf::CircleShape(7);
	ballShape.setFillColor(sf::Color::White);
	ballShape.setOutlineColor(sf::Color::Black);
	ballShape.setOutlineThickness(2.f);

	setPosition(900, 870);

	direction.x = -1;
	direction.y = -1;
}

void Ball::handleCollisions()
{
	if (position.x < GameManager::grid.tiles[0].startX) {
		direction.x = 1;
	} else if (position.x > GameManager::grid.tiles[GameManager::grid.getSize() - 1].startX + GameManager::grid.tiles[0].width) {
		direction.x = -1;
	} else if (position.y < GameManager::grid.tiles[0].startY) {
		direction.y = 1;

	} else if (Utils::collides(ballShape.getGlobalBounds(), GameManager::player->getPlayerShape().getGlobalBounds())
		&& ballShape.getGlobalBounds().left <= GameManager::player->getPlayerShape().getGlobalBounds().left + (GameManager::player->getPlayerShape().getSize().x / 2)) {

		direction.x = -1;
		direction.y = -1;

		GameManager::player->doHeal(0.5f);
		GameManager::player->setFillColor(sf::Color::Green);
		GameManager::points++;
	} else if (Utils::collides(ballShape.getGlobalBounds(), GameManager::player->getPlayerShape().getGlobalBounds())
		&& ballShape.getGlobalBounds().left >= GameManager::player->getPlayerShape().getGlobalBounds().left + (GameManager::player->getPlayerShape().getSize().x / 2)) {

		direction.x = 1;
		direction.y = -1;
		GameManager::player->doHeal(0.5f);
		GameManager::player->setFillColor(sf::Color::Green);
		GameManager::points++;
	} else {
		Tile* tile = GameManager::grid.fetchTile(sf::Vector2i(position.x, position.y));

		if (tile != nullptr && tile->showSprite
			&& Utils::collides(ballShape.getGlobalBounds(), tile->sprite->getGlobalBounds())
			) {

			tile->collide();

			direction.x = Utils::getRandom(1, 2) == 1 ? 1 : -1;
			direction.y = Utils::getRandom(1, 2) == 1 ? 1 : -1;

			GameManager::player->setFillColor(sf::Color::White);
			GameManager::player->doHeal(0.5f);
			GameManager::points += 2;
		}

	}
}



void Ball::setPosition(int x, int y)
{
	Entity::setPosition(x, y);
	ballShape.setPosition(x, y);
}

void Ball::update(sf::RenderWindow &m_window)
{
	Entity::update(m_window);

	handleCollisions();

	position.x += (direction.x * speed);
	position.y += (direction.y * speed);

	ballShape.setPosition(position.x, position.y);

}

void Ball::render(sf::RenderWindow & m_window)
{
	Entity::render(m_window);

	m_window.draw(ballShape);
}
