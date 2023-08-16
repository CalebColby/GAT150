#pragma once
#include "Framework/Components/Component.h"
#include "Audio/AudioSystem.h"

class WeaponComponent : public neu::Component
{
public:
	/*
	Bullet(float speed, const neu::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		neu::g_audioSystem.PlayOneShot("laser");
		lifespan = 1.0f;
		
	}
	*/

	WeaponComponent(float speed) : speed {speed}
	{
		neu::g_audioSystem.PlayOneShot("laser");
	}

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(neu::Actor* other);
	void Read(const neu::json_t& value);

	friend class SpaceGame;

private:
	float speed = 0;
};