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
		Actor(const neu::Transform& transform, float lifespan = -1.0f) :
			transform{ transform },
			lifespan{ lifespan }
		{}
		Actor(const Actor& other);
		virtual ~Actor() {
			OnDestroy();
		}


		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(neu::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T = Component>
		T* GetComponent();

		virtual void OnCollisionEnter(Actor* other) {}
		virtual void OnCollisionExit(Actor* other) {}


		friend class Scene;
		friend class Game;
		friend class Emitter;
		friend class Enemy;
		friend class Player;
		friend class Actor;
		friend class Component;

	public:
		neu::Transform transform;
		std::string tag;
		bool destroyed = false;
		bool persistent = false;
		bool prototype = false;

		class Scene* m_scene = nullptr;

	protected:
		std::vector<std::unique_ptr<Component>> components;

		float lifespan = -1.0f;

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