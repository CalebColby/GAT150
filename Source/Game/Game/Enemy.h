#pragma once
#include "Framework/Actor.h"

class Enemy : public neu::Actor
{
public:
	Enemy(float speed, float turnRate, const neu::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = neu::randomf(2.5f, 3.5f);
		m_fireTimer = m_fireRate;
	}

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

	friend class SpaceGame;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
};