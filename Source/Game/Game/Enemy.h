#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

class Enemy : public neu::Actor
{
public:
	CLASS_DECLARATION(Enemy)

	Enemy() = default;
	Enemy(float speed, float turnRate, const neu::Transform& transform) :
		Actor{ transform },
		speed{ speed },
		turnRate{ turnRate }
	{
		m_fireRate = neu::randomf(2.5f, 3.5f);
		m_fireTimer = m_fireRate;
	}

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollisionEnter(Actor* other) override;

	friend class SpaceGame;

private:
	float speed = 0;
	float turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;

	neu::PhysicsComponent* m_physicsComponent;
};