#include "Player.h"
#include "Bullet.h"
#include "Rocket.h"
#include "SpaceGame.h"

#include "Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

bool Player::Initialize()
{
	Actor::Initialize();

	m_physicsComponent = GetComponent<neu::PhysicsComponent>();
	auto collcomp = GetComponent<neu::CollisionComponent>();
	auto renComp = GetComponent<neu::RenderComponent>();
	if (collcomp && renComp)
	{
		float scale = m_transform.scale;
		collcomp->m_radius = renComp->GetRadius() * scale * 0.75f;
	}

	return true;
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	//Movement
	float rotate = 0;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * dt;

	float thrust = 0;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_transform.rotation);

	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * thrust * neu::g_Time.GetDeltaTime();
	m_transform.position.x = neu::Wrap(m_transform.position.x, (float)neu::g_renderer.GetWidth());
	m_transform.position.y = neu::Wrap(m_transform.position.y, (float)neu::g_renderer.GetHeight());

	// fire weapon
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!neu::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		//create bullet
		neu::Transform transform1{m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>( 400.0f, transform1);
		
		auto component = std::make_unique<neu::SpriteRenderComponent>();
		component->m_texture = GET_RESOURCE(neu::Texture, "Bullet.png", neu::g_renderer);
		bullet->AddComponent(std::move(component));

		auto collComp = std::make_unique<neu::CircleCollisionComponent>();
		collComp->m_radius = 30.0f;
		bullet->AddComponent(std::move(collComp));

		bullet->Initialize();

		bullet->m_tag = "PlayerBullet";
		m_scene->Add(std::move(bullet));

		if (m_poweredUp)
		{
			//create bullet
			neu::Transform transform2{m_transform.position, m_transform.rotation + neu::DegreesToRadians(15), 1};
			bullet = std::make_unique<Bullet>(400.0f, transform2);
			component = std::make_unique<neu::SpriteRenderComponent>();
			component->m_texture = GET_RESOURCE(neu::Texture, "Bullet.png", neu::g_renderer);
			bullet->AddComponent(std::move(component));
			collComp = std::make_unique<neu::CircleCollisionComponent>();
			collComp->m_radius = 30.0f;
			bullet->AddComponent(std::move(collComp));
			bullet->m_tag = "PlayerBullet";
			bullet->Initialize();
			m_scene->Add(std::move(bullet));

			//create bullet
			neu::Transform transform3{m_transform.position, m_transform.rotation + neu::DegreesToRadians(-15), 1};
			bullet = std::make_unique<Bullet>(400.0f, transform3);
			component = std::make_unique<neu::SpriteRenderComponent>();
			component->m_texture = GET_RESOURCE(neu::Texture, "Bullet.png", neu::g_renderer);
			bullet->AddComponent(std::move(component));
			collComp = std::make_unique<neu::CircleCollisionComponent>();
			collComp->m_radius = 30.0f;
			bullet->AddComponent(std::move(collComp));
			bullet->m_tag = "PlayerBullet";
			bullet->Initialize();
			m_scene->Add(std::move(bullet));
		}
	}

	//fire Rocket
	if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_R) &&
		!neu::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_R) && 
		m_game->GetScore() >= 50)
	{
		//create rocket
		neu::Transform transform{m_transform.position, m_transform.rotation + neu::DegreesToRadians(180), m_transform.scale};
		std::unique_ptr<Rocket> rocket = std::make_unique<Rocket>(m_speed * 1.5f, transform);

		auto rocketPhysics = std::make_unique<neu::EnginePhysicsComponent>();
		rocketPhysics->m_damping = 0.9f;
		rocket->AddComponent(std::move(rocketPhysics));

		auto sprite = std::make_unique<neu::SpriteRenderComponent>();
		sprite->m_texture = GET_RESOURCE(neu::Texture, "Rocket.png", neu::g_renderer);
		rocket->AddComponent(std::move(sprite));

		auto collComp = std::make_unique<neu::CircleCollisionComponent>();
		collComp->m_radius = 30.0f;
		rocket->AddComponent(std::move(collComp));

		rocket->m_tag = "Rocket";
		rocket->m_scene = m_scene;
		rocket->Initialize();
		m_scene->Add(std::move(rocket));
		//firing Rockets costs Score
		m_game->AddPoints(-50);
	}

	neu::g_Time.SetTimeScale(neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_T) ? 0.5f : 1.0f);

	if (m_health <= 0)
	{
		neu::g_audioSystem.PlayOneShot("hit");
		m_game->SetLives(m_game->GetLives() - 1);
		m_destroyed = true;
	}
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "EnemyBullet")
	{
		m_health -= neu::randomf(0.5f, 5.5f);
	}

	if (other->m_tag == "Enemy")
	{
		m_game->SetLives(m_game->GetLives() - 1);
		m_destroyed = true;
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
	}
}

void Player::PowerUp()
{
	if (!m_poweredUp)
	{
		m_poweredUp = true;
		neu::g_audioSystem.PlayOneShot("PowerUp");
	}
}
