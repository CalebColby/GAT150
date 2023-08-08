#pragma once
#include "PhysicsComponent.h"

namespace neu
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:

	public:


		// Inherited via PhysicsComponent
		virtual void Update(float dt) override;

		virtual void ApplyForce(const vec2& force) override;

	};
}
