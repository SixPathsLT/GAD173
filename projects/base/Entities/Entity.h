#pragma once
#include "AnimatedSprite.h"
#include "ResourceManager.h"
class Entity
{

	struct HealthBar {
		sf::RectangleShape innerBarRect;
		sf::RectangleShape outerBarRect;
		sf::Text* text = new sf::Text();

		HealthBar() {
			innerBarRect = sf::RectangleShape(sf::Vector2f(100, 15));
			outerBarRect = sf::RectangleShape(sf::Vector2f(100, 15));
			innerBarRect.setOutlineThickness(1);

			sf::Color color = sf::Color::Red;
			innerBarRect.setFillColor(sf::Color(color.r, color.g, color.b, 200));

			color = sf::Color::Green;
			outerBarRect.setFillColor(sf::Color(color.r, color.g, color.b, 150));

			text->setFont(ResourceManager::FONT_BLUE_HIGH);
			text->setCharacterSize(15);
		}

		void setPosition(int x, int y) {
			innerBarRect.setPosition(x, y);
			outerBarRect.setPosition(x, y);

			sf::FloatRect localRect = innerBarRect.getLocalBounds();
			text->setOrigin((localRect.left + localRect.width) / 2, (localRect.top + localRect.height) / 2);
			text->setPosition((x + innerBarRect.getSize().x) - (text->getLocalBounds().width / 2), (y + innerBarRect.getSize().y) - (text->getLocalBounds().height) + 1);
		}
	};

protected:
	float max_health;
	float health;

	int speed;
	bool dead = false;

	sf::Clock clock;
	sf::Vector2i position;
	sf::Vector2i direction;
	HealthBar healthBar;
	AnimatedSprite animatedSprite;

public:
	Entity(float health = 100, int speed = 1);

	void doDamage(float damage);
	void doHeal(float heal);
	void setHealth(float health);
	void setDirection(int x, int y);
	virtual void setPosition(int x, int y);
	virtual void update(sf::RenderWindow &m_window);
	virtual void render(sf::RenderWindow &m_window);
	virtual void updateHealth();

	inline float getHealth() { return health; }
	inline int &getSpeed() { return speed; }
	inline sf::Vector2i &getPosition() { return position; } 
	inline sf::Vector2i &getDirection() { return direction; }
	inline sf::Clock &getClock() { return clock; }
	inline bool &isDead() { return dead; }
	inline AnimatedSprite &getAnimatedSprite() { return animatedSprite; }
};

