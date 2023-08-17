#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Weapon : public neu::Actor
{
public:
	
	Weapon(float speed, const neu::Transform& transform) :
		Actor{ transform },
		speed{ speed }
	{
		neu::g_audioSystem.PlayOneShot("laser");
		lifespan = 1.0f;
		
	}

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(neu::Actor* other);
	void Read(const neu::json_t& value) override;

	friend class SpaceGame;

private:
	float speed = 0;
};