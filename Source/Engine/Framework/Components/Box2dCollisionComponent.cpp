#include "Box2DCollisionComponent.h"
#include "Box2DPhysicsComponent.h"
#include "Framework/Actor.h"
#include "Framework/Components/SpriteRenderComponent.h"

namespace neu
{
	CLASS_REGISTER(Box2DCollisionComponent)

		bool Box2DCollisionComponent::Initialize()
	{
		m_physics = m_owner->GetComponent<Box2DPhysicsComponent>();
		if (m_physics)
		{
			auto SpriteComponent = m_owner->GetComponent<SpriteRenderComponent>();
			if (SpriteComponent)
			{
				if (data.size.x == 0 && data.size.y == 0)
				{
					data.size = vec2{ SpriteComponent->source.w, SpriteComponent->source.h };
				}
				data.offset = SpriteComponent->origin - vec2{ 0.5f, 0.5f };
			}

			data.size *= scaleOffset * m_owner->transform.scale;

			if (m_physics->m_body->GetType() == b2_staticBody) PhysicsSystem::Instance().SetCollisionBoxStatic(m_physics->m_body, data, m_owner);
			else PhysicsSystem::Instance().SetCollisionBox(m_physics->m_body, data, m_owner);
		}

		return true;
	}

	void Box2DCollisionComponent::Update(float dt)
	{
		
	}

	bool Box2DCollisionComponent::ModifyCollision(const float sizeOffset, bool restore)
	{
		if (!m_physics) return false;

		if (!m_changedValues) return false;
		m_changedValues = false;

		

		PhysicsSystem::CollisionData newData = data;
		if(!restore) newData.size *= sizeOffset;
		if (m_physics->m_body->GetType() == b2_staticBody) PhysicsSystem::Instance().SetCollisionBoxStatic(m_physics->m_body, newData, m_owner);
		else PhysicsSystem::Instance().SetCollisionBox(m_physics->m_body, newData, m_owner);

		return true;
	}

	void Box2DCollisionComponent::Read(const json_t& value)
	{
		READ_NAME_DATA(value, "size", data.size);
		READ_NAME_DATA(value, "density", data.density);
		READ_NAME_DATA(value, "friction", data.friction);
		READ_NAME_DATA(value, "restitution", data.restitution);
		READ_NAME_DATA(value, "isTrigger", data.isTrigger);

		READ_DATA(value, scaleOffset);
	}
}