#pragma once

#include "Component.h"
#include "Physics/PhysicsSystem.h"

namespace neu
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* other) { return true; }
		virtual bool ModifyCollision(const float sizeOffset, bool restore = false) { return true; }

	public:
		float m_radius = 0.0f;
		bool m_changedValues = false;

	protected:
		PhysicsSystem::CollisionData data;
	};
}