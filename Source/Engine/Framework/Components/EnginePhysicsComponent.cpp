#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace neu
{
	CLASS_REGISTER(EnginePhysicsComponent);

	void EnginePhysicsComponent::Update(float dt)
	{
		m_owner->transform.position += m_velocity * dt;
		m_velocity *= std::pow(1 - m_damping, dt);
	}

	void EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}

	void EnginePhysicsComponent::Read(const json_t& value)
	{
		//
	}
}
