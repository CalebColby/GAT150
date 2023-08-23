#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

class Player : public neu::Actor
{
public:
	Player() = default;
	Player(float speed, float turnRate, const neu::Transform& transform) : 
		Actor{ transform },
		speed{ speed },
		turnRate{ turnRate }
	{}

	CLASS_DECLARATION(Player)

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
	//void Read(const neu::json_t& value) override;

	void PowerUp();

	friend class SpaceGame;

private:
	float speed = 0;
	float turnRate = 0;
	float m_health = 100.0f;

	bool m_poweredUp = false;

	neu::PhysicsComponent* m_physicsComponent = nullptr;
};