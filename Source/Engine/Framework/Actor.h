#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
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
		Actor(const neu::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(neu::Renderer& renderer);
		virtual void OnCollision(Actor* other) {}

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }

		void AddForce(vec2 force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		friend class Scene;
		friend class Game;
		friend class Emitter;
		friend class Enemy;
		friend class Actor;

		neu::Transform m_transform;
		std::string m_tag;

	protected:
		bool m_destroyed = false;
		float m_lifespan = -1.0f;

		vec2 m_velocity;
		float m_damping = 0.9f;

		std::shared_ptr<Model> m_model;
		class Scene* m_scene = nullptr;
		class Game* m_game = nullptr;
	};
}