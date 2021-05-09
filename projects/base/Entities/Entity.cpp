#include "Entity.h"
#include <iostream>

Entity::Entity(float health, int speed) {
	this->max_health = health;
	this->health = health;
	this->speed = speed;

}

void Entity::setPosition(int x, int y) {
	position.x = x;
	position.y = y;
	animatedSprite.spriteSheet.setPosition(position.x, position.y);

	if (health >= 0) {
		healthBar.setPosition(position.x, position.y - 10);
	}

}

void Entity::doDamage(float damage)
{
	if (isDead())
		return;

	health -= damage;

	if (health < 0)
		health = 0;

	if (health <= 0)
		dead = true;

	updateHealth();
}

void Entity::doHeal(float heal)
{
	if (isDead())
		return;

	health += heal;

	if (health > max_health)
		health = max_health;

	updateHealth();
}

void Entity::setHealth(float health)
{
	if (health < 0)
		health = 0;
	else if (health > max_health)
		health = max_health;

	this->health = health;

	updateHealth();
}

void Entity::setDirection(int x, int y)
{
	direction.x = x;
	direction.y = y;
}

void Entity::update(sf::RenderWindow &m_window) {

	animatedSprite.update();
}

void Entity::render(sf::RenderWindow &m_window) {
	animatedSprite.render(m_window);
	updateHealth();
	if (health >= 0) {
		m_window.draw(healthBar.innerBarRect);
		m_window.draw(healthBar.outerBarRect);
		m_window.draw(*healthBar.text);
	}
}

void Entity::updateHealth()
{
	if (health >= 0) {
		healthBar.setPosition(position.x, position.y);
		healthBar.text->setString(std::to_string((int)health) + "/" + std::to_string((int)max_health));
		healthBar.outerBarRect.setScale(health / max_health, healthBar.outerBarRect.getScale().y);
	}
}
