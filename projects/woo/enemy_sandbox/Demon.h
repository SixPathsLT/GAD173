#pragma once
#include "kage2dutil/gameobject.h"

class Demon : public kage::GameObject
{
public:
	Demon();
	~Demon();

	//void render();
	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);
};
