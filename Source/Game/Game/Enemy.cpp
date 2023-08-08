#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "SpaceGame.h"

#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Input/InputSystem.h"


void Enemy::Update(float dt)
{
	Actor::Update(dt);

	auto player = m_scene->GetActor<Player>();
	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	if (player)
	{
		neu::vec2 direction = player->m_transform.position - m_transform.position;

		float turnAngle = neu::vec2::SignedAngle(forward, direction.Normalized());

		m_transform.rotation += turnAngle * dt;

		float angle = neu::vec2::Angle(forward, direction.Normalized());
		if (angle < neu::DegreesToRadians(30.0f)) 
		{
			//fire
			if (m_fireTimer <= 0)
			{
				//create bullet
				neu::Transform transform{m_transform.position, m_transform.rotation, 1};
				std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(400.0f, transform);
				bullet->m_tag = "EnemyBullet";
				m_scene->Add(std::move(bullet));
				m_fireTimer = neu::randomf(m_fireRate - 0.5f, m_fireRate + 0.5f);
			}
		}
	}
	m_transform.position += forward * m_speed * neu::g_Time.GetDeltaTime();
	m_transform.position.x = neu::Wrap(m_transform.position.x, (float)neu::g_renderer.GetWidth());
	m_transform.position.y = neu::Wrap(m_transform.position.y, (float)neu::g_renderer.GetHeight());

	m_fireTimer -= dt;
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "PlayerBullet" || other->m_tag == "RocketBullet" || other->m_tag == "Rocket")
	{
		m_destroyed = true;
		m_game->AddPoints(other->m_tag == "PlayerBullet" ? 100 : (other->m_tag == "Rocket" ? 50 : 200)); 
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
		neu::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<neu::Emitter>(transform, data, 0.1f);
		m_scene->Add(std::move(emitter));
	}
}
