#pragma once
#include "Framework/Actor.h"
#include <Audio/AudioSystem.h>


class Rocket : public neu::Actor
{
public:
	CLASS_DECLARATION(Rocket)

	Rocket() = default;
	Rocket(float speed, const neu::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		neu::g_audioSystem.PlayOneShot("laser");
		//m_lifespan = 2.0f;
	}

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollisionEnter(Actor* other) override;

	friend class SpaceGame;
	friend class Player;

private:
	float m_speed = 0;
};