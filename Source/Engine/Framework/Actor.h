#pragma once
#include "Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace neu
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const neu::Transform& transform) :
			transform{ transform }
		{}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(neu::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T = Component>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {}


		friend class Scene;
		friend class Game;
		friend class Emitter;
		friend class Enemy;
		friend class Actor;


	public:
		neu::Transform transform;
		std::string tag;
		bool destroyed = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;

		
		float lifespan = -1.0f;

		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& comp : components)
		{
			T* result = dynamic_cast<T*>(comp.get());
			if (result) return result;
		}

		return nullptr;
	}
}