#pragma once
#include "Entities/Entity.h"
class Player : public Entity
{

private:
	sf::RectangleShape playerShape;

public:
	Player(float health, int speed);

	void setFillColor(sf::Color color);
	void setPosition(int x, int y) override;
	void update(sf::RenderWindow &m_window) override;
	void render(sf::RenderWindow &m_window) override;

	inline sf::RectangleShape &getPlayerShape() { return playerShape; }
};

