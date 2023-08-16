#include "WeaponComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool WeaponComponent::Initialize()
{
	auto collcomp = m_owner->GetComponent<neu::CollisionComponent>();
	auto renComp = m_owner->GetComponent<neu::RenderComponent>();
	if (collcomp && renComp)
	{
		float scale = m_owner->transform.scale;
		collcomp->m_radius = renComp->GetRadius() * scale;
	}

	return true;
}

void WeaponComponent::Update(float dt)
{

	Component::Update(dt);

	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_owner->transform.rotation);
	m_owner->transform.position += forward * speed * neu::g_Time.GetDeltaTime();
	m_owner->transform.position.x = neu::Wrap(m_owner->transform.position.x, (float)neu::g_renderer.GetWidth());
	m_owner->transform.position.y = neu::Wrap(m_owner->transform.position.y, (float)neu::g_renderer.GetHeight());
}

void WeaponComponent::OnCollision(neu::Actor* other)
{
	m_owner->destroyed = true;
}
