#include "Actor.h"
#include "Components/RenderComponent.h"

namespace neu
{
	CLASS_REGISTER(Actor);

	bool Actor::Initialize()
	{
		for (auto& comp : m_components)
		{
			comp->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& comp : m_components)
		{
			comp->OnDestroy();
		}
	}
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = m_lifespan <= 0;
		}

		for (auto& comp : m_components)
		{
			comp->Update(dt);
		}
	}

	void Actor::Draw(neu::Renderer& renderer)
	{
		//m_model->Draw(renderer, m_transform);

		for (auto& comp : m_components)
		{
			RenderComponent* renComp = dynamic_cast<RenderComponent*>(comp.get());
			if (renComp)
			{
				renComp->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}

	bool Actor::Read(const rapidjson::Value& value)
	{


		return true;
	}
}