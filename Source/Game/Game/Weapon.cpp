#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

CLASS_REGISTER(Weapon) 

bool Weapon::Initialize()
{
	Actor::Initialize();

	auto collcomp = GetComponent<neu::CollisionComponent>();
	auto renComp = GetComponent<neu::RenderComponent>();
 	if (collcomp && renComp)
	{
		float scale = transform.scale;
		collcomp->m_radius = renComp->GetRadius() * scale;
	}
	m_physicsComponent = GetComponent<neu::PhysicsComponent>();
	return true;
}

void Weapon::Update(float dt)
{
	Actor::Update(dt);

	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(transform.rotation);
	//transform.position += forward * speed * neu::g_Time.GetDeltaTime();
	if(m_physicsComponent) m_physicsComponent->ApplyForce(forward * speed * dt);

	transform.position.x = neu::Wrap(transform.position.x, (float)neu::g_renderer.GetWidth());
	transform.position.y = neu::Wrap(transform.position.y, (float)neu::g_renderer.GetHeight());
}

void Weapon::OnCollisionEnter(neu::Actor* other)
{
	destroyed = true;
}

void Weapon::Read(const neu::json_t& value)
{
	Actor::Read(value);

	READ_DATA(value, speed);
}
