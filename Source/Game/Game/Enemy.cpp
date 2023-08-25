#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"

#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

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

	auto player = m_scene->GetActor<Player>();
	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(transform.rotation);



	if (player)
	{
		neu::vec2 direction = player->transform.position - transform.position;

		float turnAngle = neu::vec2::SignedAngle(forward, direction.Normalized());

		if(m_physicsComponent) m_physicsComponent->ApplyTorque(turnAngle * dt);

		float angle = neu::vec2::Angle(forward, direction.Normalized());
		/*
		if (angle < neu::DegreesToRadians(30.0f)) 
		{
			
			//fire
			if (m_fireTimer <= 0)
			{
				//create bullet
				neu::Transform transform{this->transform.position, this->transform.rotation, 1};
				auto bullet = INSTANTIATE(Weapon, "Weapon"); //std::make_unique<Weapon>();

				bullet->transform = transform;

				bullet->tag = "EnemyBullet";
				m_scene->Add(std::move(bullet));
				m_fireTimer = neu::randomf(m_fireRate - 0.5f, m_fireRate + 0.5f);
			}
		}
		*/
	}
	if(m_physicsComponent) m_physicsComponent->ApplyForce(forward * speed * dt);
	transform.position.x = neu::Wrap(transform.position.x, (float)neu::g_renderer.GetWidth());
	transform.position.y = neu::Wrap(transform.position.y, (float)neu::g_renderer.GetHeight());

	m_fireTimer -= dt;
}

void Enemy::OnCollisionEnter(Actor* other)
{
	if (other->tag == "PlayerBullet" || other->tag == "RocketBullet" || other->tag == "Rocket")
	{
		neu::EventManager::Instance().DispatchEvent("OnAddPoints", (other->tag == "PlayerBullet" ? 100 : (other->tag == "Rocket" ? 50 : 200)));
		destroyed = true;
		//m_game->AddPoints(other->tag == "PlayerBullet" ? 100 : (other->tag == "Rocket" ? 50 : 200)); 
		//The Rocket Itself gives enough points to refund its cost on hit, but chain kills from the rockets bullet spread give enough points for 4 rockets 
		//and are what make the rocket worth using if one is going for a high score
		neu::g_audioSystem.PlayOneShot("hit");
		//Potintially Drop Power Up
		if (neu::random(101) < 25)
		{
			auto player = m_scene->GetActor<Player>();
			if (player) player->PowerUp();
		}


		//Destruction Particles
		neu::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 0;
		data.angle = 0;
		data.angleRange = neu::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = neu::Color{ 1, 0, 0, 1 };
		//data.color = other->
		neu::Transform transform{ { this->transform.position }, 0, 1 };
		auto emitter = std::make_unique<neu::Emitter>(transform, data, 0.1f);
		m_scene->Add(std::move(emitter));
	}
}

void Enemy::Read(const neu::json_t& value)
{
	Actor::Read(value);

	READ_DATA(value, turnRate);
	READ_DATA(value, speed);
}
