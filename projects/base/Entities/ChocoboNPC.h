#pragma once
#include "Entities/Entity.h"

#define TOTAL_FIRE_ATTACKS 6

class ChocoboNPC : public Entity
{

	struct FireAttack {
		bool hit = false;
		int x = 0;
		int y = 0;
		AnimatedSprite fireAnimatedSprite;
		AnimatedSprite explosionAnimatedSprite;

		void setPosition(int x, int y);
	};

private:
	int power = 1;
	FireAttack fireAttacks[TOTAL_FIRE_ATTACKS];
	int currentFireAttackIndex = 0;

public:
	ChocoboNPC(float health, int speed);

	void processAttacks();
	void update(sf::RenderWindow &m_window) override;
	void render(sf::RenderWindow &m_window) override;
};

