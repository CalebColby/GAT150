#pragma once
#include "Framework/Actor.h"
#include "Audio/AudioSystem.h"

class Weapon : public neu::Actor
{
public:
	CLASS_DECLARATION(Weapon)

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(neu::Actor* other);

	friend class SpaceGame;

private:
	float speed = 0;
};