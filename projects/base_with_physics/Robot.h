#pragma once
#include "kage2dutil/gameobject.h"

class Robot : public kage::GameObject
{
public:
	Robot();
	~Robot();

	//void render();
	void update(float deltaT);
	void onCollision(GameObject *obj);
	void onCollision(b2Fixture *fix);
};
