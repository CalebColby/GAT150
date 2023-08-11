#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Bullet : public neu::Actor
{
public:
	Bullet(float speed, const neu::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		neu::g_audioSystem.PlayOneShot("laser");
		m_lifespan = 1.0f;
		
	}

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

	friend class SpaceGame;

private:
	float m_speed = 0;
};