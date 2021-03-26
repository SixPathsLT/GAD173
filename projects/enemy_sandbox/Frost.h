#pragma once
#include "kage2dutil/gameobject.h"

class Frost : public kage::GameObject
{
public:
	Frost();
	~Frost();

	//void render();
	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);
};
