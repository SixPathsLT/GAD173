#include "Rabbit.h"
#include "example.h"

Rabbit::Rabbit()
{
	m_sprite = kage::TextureManager::getSprite("data/zazaka.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("Rabbit");

	m_physicsStyle = GameObject::e_psBox2D;

	// Make a Box2D body
	m_body = kage::Physics::BodyBuilder()
				.pos(0, 0)
				.userData(this)	// This lets the body know which GameObject owns it
				.build();
	m_body->SetGravityScale(0);
	// Make a fixture (collision shape) for the body
	kage::Physics::CircleBuilder()
		.radius(0.4)
		.mass(1)
		.build(m_body); // We need to tell the builder which body to attach to
}

Rabbit::~Rabbit()
{

}

void Rabbit::update(float deltaT)
{
	// Do logic here
	kf::Vector2 vel;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		vel.x = -3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		vel.x = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		vel.y = -3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		vel.y = 3;
	}
	velocity(vel);

	GameObject::update(deltaT);
}

void Rabbit::onCollision(GameObject *obj)
{
	//if (obj->m_tags.has("enemy"))
	//{
		//m_dead = true;		// kills itself
		//obj->m_dead = true;	// kills the other object
	//}
	
}

void Rabbit::onCollision(b2Fixture *fix)
{
	//if ((int)(fix->GetUserData()) == 1234) // Fake ID value 1234
	//{
	//}
}
