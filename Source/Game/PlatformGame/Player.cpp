#include "Player.h"

#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

CLASS_REGISTER(Player)

bool Player::Initialize()
{
	Actor::Initialize();

	m_physicsComponent = GetComponent<neu::PhysicsComponent>();
	m_collisionComponent = GetComponent<neu::CollisionComponent>();
	m_animComponent = GetComponent<neu::SpriteAnimRenderComponent>();

	return true;
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	//Upkeep
	bool isCrouching = false;
	bool onGround = (groundCount > 0);
	bool isDead = (m_health <= 0);
	neu::vec2 velocity = m_physicsComponent->m_velocity;
	if (m_hitTimer > 0) m_hitTimer -= dt;


	//Movement
	float dir = 0;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_A) && !isDead) dir = -1;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_D) && !isDead) dir =  1;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_S) && onGround && !isDead) isCrouching = true;

	neu::vec2 forward = neu::vec2{ 1, 0 };

	if (dir)
	{
		velocity.x += dt * speed * dir * ((!onGround || isCrouching || m_isAttacking) ? 0.25f : 1);
		if(isCrouching) velocity.x = neu::Clamp(velocity.x, -maxSpeed/2, maxSpeed/2);
		else velocity.x = neu::Clamp(velocity.x, -maxSpeed, maxSpeed);
		m_physicsComponent->SetVelocity(velocity);
	}

	//Jump

	if (onGround && !isDead &&
		neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!neu::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		neu::vec2 up{ 0, -1 };
		m_physicsComponent->SetVelocity(velocity + (up * jumpForce));
	}
	m_physicsComponent->SetGravityScale((velocity.y > 0) ? 3.0f : 1.0f);

	//Attack
	if (onGround && !isDead && 
		neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_Q) &&
		!neu::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_Q))
	{
		m_isAttacking = true;
		attackCount = 1;
	}

	if (m_isAttacking) 
	{
		auto PlayerAttack = INSTANTIATE(neu::Actor, "PlayerAttack");
		PlayerAttack->transform = this->transform;
		PlayerAttack->transform.position.x = this->transform.position.x + (facing * 25);
		PlayerAttack->Initialize();
		m_scene->Add(std::move(PlayerAttack));

		attackTimer -= dt;
		if (attackTimer <= 0)
		{
			attackTimer = 0.5f;
			attackCount--;
			if (attackCount <= 0) m_isAttacking = false;
		}
	}

	//Animation
	if (dir != 0) m_animComponent->flipH = (dir < 0);

	if (isDead) m_animComponent->SetSequence("death"); 
	else if (m_hitTimer > 0) m_animComponent->SetSequence("hit");
	else if (!onGround) m_animComponent->SetSequence((velocity.y <= 0) ? "jump" : "fall");
	else if (isCrouching) m_animComponent->SetSequence((m_isAttacking) ? "crouchAttack" :  
			(std::fabs(velocity.x) > 0.2f) ? "crouchWalk" : "crouch");
	else if (m_isAttacking) m_animComponent->SetSequence("attack");
	else if (m_health <= 0) m_animComponent->SetSequence("death");
	else m_animComponent->SetSequence((std::fabs(velocity.x) > 0.2f) ? "run" : "idle");
}

void Player::OnCollisionEnter(Actor* other)
{
	if (other->tag == "Enemy" && m_hitTimer <= 0)
	{
		m_health -= neu::randomf(5.0f, 10.0f);
		m_hitTimer = 0.3;
	}

	if (other->tag == "Ground") groundCount++;
	if (other->tag == "Coin") 
	{
		other->destroyed = true;
	}
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