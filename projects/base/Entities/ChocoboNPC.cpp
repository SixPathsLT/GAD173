#include "ChocoboNPC.h"
#include <iostream>
#include "GameManager.h"
#include "Utils.h"


ChocoboNPC::ChocoboNPC(float health, int speed) : Entity(health, speed) {
	animatedSprite.setAnimation(AnimatedSprite::CHOCOBO, 90);
	animatedSprite.setRow(1);
	animatedSprite.play(true);

	for (int i = 0; i < TOTAL_FIRE_ATTACKS; i++) {
		fireAttacks[i].fireAnimatedSprite.setAnimation(AnimatedSprite::FIRE_EFFECT, 100);
		fireAttacks[i].fireAnimatedSprite.play(true);

		fireAttacks[i].explosionAnimatedSprite.setAnimation(AnimatedSprite::EXPLOSION_EFFECT, 50);
	}
}


void ChocoboNPC::processAttacks()
{
	direction.y = 0;

	for (int i = 0; i < TOTAL_FIRE_ATTACKS; i++) {
		FireAttack& fireAttack = fireAttacks[i];
		if (fireAttack.y == 0) {
			if (Utils::getRandom(1, 300 / power) == 1) {
				int offset = direction.x > 0 ? 50 : -30;
				fireAttack.setPosition(position.x + offset, position.y);
			}
		} else {
			fireAttack.y += 5;
			fireAttack.setPosition(fireAttack.x, fireAttack.y);
			fireAttack.fireAnimatedSprite.update();

			if (Utils::collides(fireAttack.fireAnimatedSprite.spriteSheet.getGlobalBounds(), GameManager::player->getPlayerShape().getGlobalBounds())) {
				fireAttack.hit = true;

				fireAttack.explosionAnimatedSprite.spriteSheet.setPosition(fireAttack.x + (fireAttack.fireAnimatedSprite.spriteWidth / 2) - (fireAttack.explosionAnimatedSprite.spriteWidth / 2), GameManager::player->getPlayerShape().getPosition().y - (fireAttack.explosionAnimatedSprite.spriteHeight / 1.4));
				fireAttack.explosionAnimatedSprite.play(false);

				GameManager::player->setFillColor(sf::Color::Red);

				fireAttack.setPosition(fireAttack.x, 1200);

			}

			if (fireAttack.hit) {
				fireAttack.explosionAnimatedSprite.update();

				float damage = 0.1f * power;
				GameManager::player->doDamage(damage);
				if (!fireAttack.explosionAnimatedSprite.isPlaying()) {
					fireAttack.hit = false;
				}
			}

			if (!fireAttack.hit && fireAttack.y > 1100) {
				currentFireAttackIndex++;
				fireAttack.setPosition(0, 0);
			}
		}


	}
}


void ChocoboNPC::update(sf::RenderWindow &m_window) {

	Entity::update(m_window);

	position.x += direction.x * speed;
	position.y += direction.y * speed;

	setPosition(position.x, position.y);

	processAttacks();

	if (dead) {
		animatedSprite.setRow(3);
		animatedSprite.setFrame(3);
		animatedSprite.play(false);
		direction.x = 0;
		direction.y = 1;
		speed = 10;
		return;
	}

	Tile startTile = GameManager::grid.tiles[0];
	Tile endTile = GameManager::grid.tiles[GameManager::grid.getSize() - 1];

	if (position.y > GameManager::grid.tiles[0].startY && clock.getElapsedTime().asMilliseconds() > 7800) {
		power++;
		direction.y = -15;
	
		clock.restart();
	}

	if (position.x < startTile.startX) {
		direction.x = 1;
		animatedSprite.setRow(2);
	} else if (position.x > endTile.startX) {
		direction.x = -1;
		animatedSprite.setRow(1);
	}

	
	if (Utils::collides(GameManager::ball->getBallShape().getGlobalBounds(), animatedSprite.spriteSheet.getGlobalBounds())) {
		doDamage(2.f);

		GameManager::ball->setDirection(Utils::getRandom(1, 2) == 1 ? 1 : -1, Utils::getRandom(1, 2) == 1 ? 1 : -1);
	}
	
	sf::Vector2i offsetPosition = sf::Vector2i(position.x + (direction.x > 0 ? animatedSprite.spriteWidth : 0), position.y + 60);
	Tile* tile = GameManager::grid.fetchTile(offsetPosition);

	if (tile != nullptr && tile->showSprite
		&& Utils::collides(offsetPosition.x, offsetPosition.y, tile->sprite->getGlobalBounds())
		) {

		sf::Color color = tile->sprite->getTexture()->copyToImage().getPixel(tile->sprite->getTexture()->getSize().x / 2, tile->sprite->getTexture()->getSize().y / 2);

		for (int i = 0; i < TOTAL_FIRE_ATTACKS; i++) {
			if (fireAttacks[i].y > 0)
				continue;

			fireAttacks[i].fireAnimatedSprite.spriteSheet.setColor(color);
			fireAttacks[i].explosionAnimatedSprite.spriteSheet.setColor(color);
		}

		tile->collide();
		doHeal(0.5f);
	}
	

}

void ChocoboNPC::render(sf::RenderWindow &m_window) {
	Entity::render(m_window);


	for (int i = 0; i < TOTAL_FIRE_ATTACKS; i++) {

		fireAttacks[i].explosionAnimatedSprite.render(m_window);

		if (fireAttacks[i].x == 0)
			continue;

		fireAttacks[i].fireAnimatedSprite.render(m_window);

	}

}

void ChocoboNPC::FireAttack::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	fireAnimatedSprite.spriteSheet.setPosition(x, y);
}


