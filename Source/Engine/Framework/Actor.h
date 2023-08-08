#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace neu
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const neu::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(neu::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T = Component>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {}

		float GetRadius() { return 15.0f; }

		friend class Scene;
		friend class Game;
		friend class Emitter;
		friend class Enemy;
		friend class Actor;

		neu::Transform m_transform;
		std::string m_tag;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;
		float m_lifespan = -1.0f;

		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& comp : m_components)
		{
			T* result = dynamic_cast<T*>(comp.get());
			if (result) return result;
		}

		return nullptr;
	}
}