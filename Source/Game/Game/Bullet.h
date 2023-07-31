#pragma once
#include "Framework/Actor.h"
#include <Audio/AudioSystem.h>

class Bullet : public neu::Actor
{
public:
	Bullet(float speed, const neu::Transform& transform, std::shared_ptr<neu::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		neu::g_audioSystem.PlayOneShot("laser");
		m_lifespan = 1.0f;
		
	}


	void Update(float dt) override;
	void OnCollision(Actor* other) override;

	friend class SpaceGame;

private:
	float m_speed = 0;
};