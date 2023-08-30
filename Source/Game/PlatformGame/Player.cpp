#include "Player.h"

#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

CLASS_REGISTER(Player)

bool Player::Initialize()
{
	Actor::Initialize();

	m_physicsComponent = GetComponent<neu::PhysicsComponent>();
	m_animComponent = GetComponent<neu::SpriteAnimRenderComponent>();

	return true;
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	bool onGround = (groundCount > 0);
	neu::vec2 velocity = m_physicsComponent->m_velocity;

	//Movement
	float dir = 0;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

	neu::vec2 forward = neu::vec2{ 1, 0 };
	
	if (dir)
	{
		velocity.x += dt * speed * dir * ((onGround) ? 1 : 0.25f);
		velocity.x = neu::Clamp(velocity.x, -maxSpeed, maxSpeed);
		m_physicsComponent->SetVelocity(velocity);
	}

	//m_physicsComponent->ApplyForce(forward * speed * dir);

	//Jump
	
	if (onGround && 
		neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!neu::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		neu::vec2 up{ 0, -1 };
		m_physicsComponent->SetVelocity(velocity + (up * jumpForce));
	}

	m_physicsComponent->SetGravityScale((velocity.y > 0) ? 3.0f : 1.0f);

	//Animation
	if (std::fabs(velocity.x) > 0.2f)
	{
		if(dir != 0) m_animComponent->flipH = (dir < 0);
		m_animComponent->SetSequence("run");
	}
	else 
	{
		m_animComponent->SetSequence("idle");
	}

	
	
}

void Player::OnCollisionEnter(Actor* other)
{
	if (other->tag == "Enemy")
	{
		//destroyed = true;
		//EVENT_DISPATCH("OnPlayerDead", 0);
	}

	if (other->tag == "Ground") groundCount++;
}

void Player::OnCollisionExit(Actor* other)
{
	if (other->tag == "Ground") groundCount--;
}


void Player::Read(const neu::json_t& value)
{
	Actor::Read(value);

	READ_DATA(value, jumpForce);
	READ_DATA(value, speed);
	READ_DATA(value, maxSpeed);
}