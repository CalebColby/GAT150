#include "Enemy.h"
#include "Player.h"

#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

CLASS_REGISTER(Enemy)

bool Enemy::Initialize()
{
	Actor::Initialize();

	m_physicsComponent = GetComponent<neu::PhysicsComponent>();


	return true;
}

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	//Movement
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		neu::vec2 direction = player->transform.position - transform.position;
		direction.Normalize();

		m_physicsComponent->ApplyForce(direction * speed);
	}
}

void Enemy::OnCollisionEnter(Actor* other)
{
	if (other->tag == "Player")
	{
		destroyed = true;
	}
}

void Enemy::OnCollisionExit(Actor* other)
{
}


void Enemy::Read(const neu::json_t& value)
{
	Actor::Read(value);

	READ_DATA(value, jumpForce);
	READ_DATA(value, speed);
}