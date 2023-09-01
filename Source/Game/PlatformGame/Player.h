#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Components/CollisionComponent.h"
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
	float maxSpeed = 0;
	float jumpForce = 1;
	float m_health = 100.0f;
	float attackTimer = 0.5f;
	float m_hitTimer = 0;
	int groundCount = 0;
	int attackCount = 0;
	int facing = 1;

	bool m_poweredUp = false;
	bool m_isAttacking = false;

	neu::PhysicsComponent* m_physicsComponent = nullptr;
	neu::CollisionComponent* m_collisionComponent = nullptr;
	neu::SpriteAnimRenderComponent* m_animComponent = nullptr;
};

