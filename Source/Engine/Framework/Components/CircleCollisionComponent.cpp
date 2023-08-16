#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace neu
{
    CLASS_REGISTER(CircleCollisionComponent);

    void CircleCollisionComponent::Update(float dt)
    {
        //
    }

    bool CircleCollisionComponent::CheckCollision(CollisionComponent* other)
    {
        float distance = m_owner->transform.position.Distance(other->GetOwner()->transform.position);
        float radius = m_radius + other->m_radius;

        return (distance <= radius);
    }
}
