#include "Rocket.h"
#include "Bullet.h"
#include "Framework/Scene.h"

void Rocket::Update(float dt)
{
	Actor::Update(dt);

	neu::vec2 forward = neu::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	//m_transform.position += forward * m_speed * dt;
	AddForce(forward);
	m_transform.position.x = neu::Wrap(m_transform.position.x, (float)neu::g_renderer.GetWidth());
	m_transform.position.y = neu::Wrap(m_transform.position.y, (float)neu::g_renderer.GetHeight());
}

void Rocket::OnCollision(Actor* other)
{
	if (other->m_tag == "Enemy")
	{
		m_destroyed = true;
		for (size_t i = 0; i < 24; i++)
		{
			//create bullets
			neu::Transform transform{m_transform.position, m_transform.rotation + neu::DegreesToRadians(15.0f * i), 1.0f};
			std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(400.0f, transform, m_model);
			bullet->m_tag = "RocketBullet";
			m_scene->Add(std::move(bullet));
		}
	}
}
