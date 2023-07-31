#pragma once
#include "Actor.h"
#include <list>

namespace neu
{
	class Renderer;
	class Actor;

	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor>);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		friend class Actor;

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
	};


	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}
}