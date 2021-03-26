#include "Frost.h"
#include "example.h"

Frost::Frost()
{
	m_sprite = kage::TextureManager::getSprite("data/frost.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Frost");
	m_tags.add("enemy");

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
	
	kage::Physics::CircleBuilder()
		.radius(0.1)
		.pos(0, 0.4)
		.mass(0)
		.sensor(true)
		.userData(1)
		.build(m_body);
}

Frost::~Frost()
{

}

void Frost::update(float deltaT)
{
	// Do logic here

	GameObject::update(deltaT);
}

void Frost::onCollision(GameObject *obj)
{
	//if (obj->m_tags.has("enemy"))
	//{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	//}
}

void Frost::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}

