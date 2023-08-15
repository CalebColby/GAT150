#pragma once

#include "CollisionComponent.h"

namespace neu
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		virtual void Update(float dt) override;
		virtual bool CheckCollision(CollisionComponent* other) override;

		CLASS_DECLARATION(CircleCollisionComponent);

	public:

	};
}
