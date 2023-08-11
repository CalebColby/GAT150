#include "Bullet.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool Bullet::Initialize()
{
	auto collcomp = GetComponent<neu::CollisionComponent>();
	auto renComp = GetComponent<neu::RenderComponent>();
	if (collcomp && renComp)
	{
		float scale = m_transform.scale;
		collcomp->m_radius = renComp->GetRadius() * scale;
	}

	return true;
}

void Bullet::Update(float dt)
{

	Actor::Update(dt);

	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * neu::g_Time.GetDeltaTime();
	m_transform.position.x = neu::Wrap(m_transform.position.x, (float)neu::g_renderer.GetWidth());
	m_transform.position.y = neu::Wrap(m_transform.position.y, (float)neu::g_renderer.GetHeight());
}

void Bullet::OnCollision(Actor* other)
{
	m_destroyed = true;
}
