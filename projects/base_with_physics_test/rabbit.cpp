#include "rabbit.h"
#include "example.h"
#include "windows.h"
#include "xinput.h"

Rabbit::Rabbit()
{
	m_sprite = kage::TextureManager::getSprite("data/zazaka.png");
	kage::centreOrigin(m_sprite);
	m_tags.add("rabbit");

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

Rabbit::~Rabbit()
{

}

int stickNum = 0;
bool normOuter = false;
bool normInner = false;
float deadZoneInner = 0.3;
bool deadZone = false;

void Rabbit::update(float deltaT)
{
	// Do logic here
	XINPUT_STATE state;
	XInputGetState(0, &state);
	kf::Vector2 stick(state.Gamepad.sThumbLX / 32768.0f, state.Gamepad.sThumbLY / 32768.0f);
	
	//if(stick.length()>1.0f)
	float x = state.Gamepad.sThumbLX / 32768.0f;
	float y = state.Gamepad.sThumbLY / 32768.0f;
	if (fabs(x) < 0.5)
		x = 0;
	kf::Vector2 force(x*10, 0);
	addForce(force);

	ImGui::Begin("Controller");
	ImGui::RadioButton("Left Stick", &stickNum, 0);
	ImGui::RadioButton("Right Stick", &stickNum, 1);
	ImGui::Checkbox("Normalise Outer", &normOuter);
	ImGui::Checkbox("Normalise Inner", &normInner);
	ImGui::Checkbox("Dead Zone", &deadZone);
	ImGui::SliderFloat("Dead Zone Inner", &deadZoneInner, 0, 1);
	ImGui::End();
	




	GameObject::update(deltaT);
}

void Rabbit::onCollision(GameObject *obj)
{
	if (obj->m_tags.has("enemy"))
	{
		m_dead = true;			// kills itself
		//obj->m_dead = true;	// kills the other object
	}
}

std::vector<kf::Vector2> positionsRaw;
std::vector<kf::Vector2> positions;

void Rabbit::render(sf::RenderWindow &rw)
{
	XINPUT_STATE state;
	XInputGetState(0, &state);
	
	kf::Vector2 stick;
	if(stickNum==0)
		stick.set(state.Gamepad.sThumbLX / 32768.0f, state.Gamepad.sThumbLY / -32768.0f);
	else
		stick.set(state.Gamepad.sThumbRX / 32768.0f, state.Gamepad.sThumbRY / -32768.0f);
	kf::Vector2 raw = stick;

	positionsRaw.push_back(raw);

	if (normOuter)
	{
		if (stick.length() > 1.0f)
			stick.normalise();
	}
	if (deadZone)
	{
		if (normInner)
		{
			float r = stick.normalise();
			if (r < deadZoneInner)
			{
				r = deadZoneInner;
			}
			stick *= (r - deadZoneInner)*(1.0/(1.0-deadZoneInner));
		}
		else
		{
			if (stick.length() < deadZoneInner)
			{
				stick.set(0, 0);
			}
			if (fabs(stick.x) < 0.3 && fabs(stick.y) < 0.3)
			{
				//stick.set(0, 0);
			}
		}
	}
	if (normInner)
	{

	}
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		XINPUT_VIBRATION vib;
		vib.wLeftMotorSpeed = 65535;
		vib.wRightMotorSpeed = 65535;
		XInputSetState(0, &vib);
	}
	else
	{
		XINPUT_VIBRATION vib;
		vib.wLeftMotorSpeed = 0;
		vib.wRightMotorSpeed = 0;
		XInputSetState(0, &vib);
	}
	positions.push_back(stick);

	kage::drawCircle(rw, kf::Vector2(960, 540), 300, 32);
	kage::drawCircle(rw, kf::Vector2(960, 540), 300*deadZoneInner, 32);

	kage::drawArrow(rw, kf::Vector2(960, 540), kf::Vector2(960, 540) + stick * 300, 10, 20, sf::Color::Cyan);
	kage::drawCircle(rw, kf::Vector2(960, 540) + raw * 300, 10, 10, sf::Color::Cyan);
	for (int i = 1; i < positions.size(); ++i)
	{
		int fade = 255 - (positions.size() - i);
		if (fade < 0) fade = 0;
		kage::drawLine(rw, positionsRaw[i - 1] * 300 + kf::Vector2(960, 540), positionsRaw[i] * 300 + kf::Vector2(960, 540), sf::Color(255, 64, 64, fade));
		kage::drawLine(rw, positions[i - 1] * 300 + kf::Vector2(960, 540), positions[i] * 300 + kf::Vector2(960, 540), sf::Color(64, 255, 64, fade));
	}

	GameObject::render(rw);
}
