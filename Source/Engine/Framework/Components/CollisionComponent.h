#pragma once

#include "Component.h"

namespace neu
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* other) = 0;

	public:
		float m_radius = 0.0f;
	};
}