#include "Rocket.h"
#include "Weapon.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

CLASS_REGISTER(Rocket)

bool Rocket::Initialize()
{
	Actor::Initialize();

	auto collcomp = GetComponent<neu::CollisionComponent>();
	auto renComp = GetComponent<neu::RenderComponent>();
	if (collcomp && renComp)
	{
		float scale = transform.scale;
		collcomp->m_radius = renComp->GetRadius() * scale;
	}

	return true;
}

void Rocket::Update(float dt)
{
	Actor::Update(dt);

	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(transform.rotation);
	//m_transform.position += forward * m_speed * dt;

	GetComponent<neu::PhysicsComponent>()->ApplyForce(forward);
	transform.position.x = neu::Wrap(transform.position.x, (float)neu::g_renderer.GetWidth());
	transform.position.y = neu::Wrap(transform.position.y, (float)neu::g_renderer.GetHeight());
}

void Rocket::OnCollisionEnter(Actor* other)
{
	if (other->tag == "Enemy")
	{
		destroyed = true;
		for (size_t i = 0; i < 24; i++)
		{
			//create bullets
			neu::Transform transform{this->transform.position, this->transform.rotation + neu::DegreesToRadians(15.0f * i), 1.0f};
			std::unique_ptr<Weapon> bullet = std::make_unique<Weapon>();

			std::unique_ptr<neu::SpriteRenderComponent> component = std::make_unique<neu::SpriteRenderComponent>();
			component->m_texture = GET_RESOURCE(neu::Texture, "Bullet.png", neu::g_renderer);
			bullet->AddComponent(std::move(component));

			auto collComp = std::make_unique<neu::CircleCollisionComponent>();
			collComp->m_radius = 30.0f;
			bullet->AddComponent(std::move(collComp));

			bullet->Initialize();

			bullet->tag = "RocketBullet";
			m_scene->Add(std::move(bullet));
		}
	}
}

void Rocket::Read(const neu::json_t& value)
{
	Actor::Read(value);
}
