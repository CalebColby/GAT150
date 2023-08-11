#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace neu
{
    void CircleCollisionComponent::Update(float dt)
    {
        //
    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* other)
    {
        float distance = m_owner->m_transform.position.Distance(other->GetOwner()->m_transform.position);
        float radius = m_radius + other->m_radius;

        return (distance <= radius);
    }
}
