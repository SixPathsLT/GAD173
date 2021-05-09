#include "Demon.h"
#include "example.h"
//#include "fireball.h"

Demon::Demon()
{
	m_sprite = kage::TextureManager::getSprite("data/demon.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Demon");

	m_physicsStyle = GameObject::e_psBox2D;

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();

	// Make a fixture (collision shape) for the body
	kage::Physics::CircleBuilder()
		.radius(0.4)
		.mass(1)
		.build(m_body); // We need to tell the builder which body to attach to
}

Demon::~Demon()
{

}

void Demon::update(float deltaT)
{
	GameObject::update(deltaT);
}

void Demon::onCollision(GameObject *obj)
{
	//if (obj->m_tags.has("enemy"))
	//{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	//}
}

void Demon::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

