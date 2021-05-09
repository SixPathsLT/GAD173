#pragma once
#include "Entities/Entity.h"

class Ball : public Entity
{

private:
	sf::CircleShape ballShape;

public:
	Ball(float health = -1, int speed = 8);
	void handleCollisions();

	void setPosition(int x, int y) override;
	void update(sf::RenderWindow &m_window) override;
	void render(sf::RenderWindow &m_window) override;

	inline sf::CircleShape &getBallShape() { return ballShape; }
};
