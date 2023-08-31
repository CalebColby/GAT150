#pragma once
#include "CollisionComponent.h"
#include <functional>

namespace neu
{
	class Box2DCollisionComponent : public CollisionComponent
	{
	public:
		using collisionFunction = std::function<void(Actor*)>;

	public:
		CLASS_DECLARATION(Box2DCollisionComponent)

		virtual bool Initialize() override;
		virtual void Update(float dt) override;

		bool ModifyCollision(const float offset, bool restore = false) override;

	private:
		vec2 scaleOffset = vec2{ 1, 1 };
		class Box2DPhysicsComponent* m_physics;
	};
}