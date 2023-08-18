#include "Actor.h"
#include "Components/RenderComponent.h"

namespace neu
{
	CLASS_REGISTER(Actor);

	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		lifespan = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : other.components)
		{
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}
	}

	bool Actor::Initialize()
	{
		for (auto& comp : components)
		{
			comp->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& comp : components)
		{
			comp->OnDestroy();
		}
	}
	void Actor::Update(float dt)
	{
		if (lifespan != -1.0f)
		{
			lifespan -= dt;
			destroyed = lifespan <= 0;
		}

		for (auto& comp : components)
		{
			comp->Update(dt);
		}
	}

	void Actor::Draw(neu::Renderer& renderer)
	{
		//m_model->Draw(renderer, m_transform);

		for (auto& comp : components)
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
		components.push_back(std::move(component));
	}

	void Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);

		if(HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform)); 

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}
}