#pragma once
#include "Framework/Actor.h"

class Player : public neu::Actor
{
public:
	Player(float speed, float turnRate, const neu::Transform& transform) : 
		Actor{ transform},
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}


	void Update(float dt) override;
	void OnCollision(Actor* other) override;

	void PowerUp();

	friend class SpaceGame;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 100.0f;

	bool m_poweredUp = false;
};