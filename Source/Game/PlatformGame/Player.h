#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Components/SpriteAnimRenderComponent.h"

class Player : public neu::Actor
{
public:
	Player() = default;
	Player(float speed, float jumpForce, const neu::Transform& transform) :
		Actor{ transform },
		speed{ speed },
		jumpForce{ jumpForce }
	{}

	CLASS_DECLARATION(Player)

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollisionEnter(Actor* other) override;
	void OnCollisionExit(Actor* other) override;

	friend class SpaceGame;

private:
	float speed = 0;
	float jumpForce = 1;
	float m_health = 100.0f;
	int groundCount = 0;

	bool m_poweredUp = false;

	neu::PhysicsComponent* m_physicsComponent = nullptr;
	neu::SpriteAnimRenderComponent* m_animComponent = nullptr;
};

