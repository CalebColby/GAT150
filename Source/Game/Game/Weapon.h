#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/Box2dPhysicsComponent.h"
#include "Audio/AudioSystem.h"

class Weapon : public neu::Actor
{
public:
	CLASS_DECLARATION(Weapon)

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollisionEnter(neu::Actor* other) override;

	friend class SpaceGame;

private:
	neu::PhysicsComponent* m_physicsComponent = nullptr;

	float speed = 0;
};