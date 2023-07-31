#pragma once
#include "Actor.h"

namespace neu
{
	struct EmitterData
	{
		// emission
		float spawnRate = 0;
		float spawnRateTimer = 0;
		bool burst = false;
		size_t burstCount = 0;

		// particle parameters
		float lifetimeMin = 0;
		float lifetimeMax = 0;
		float speedMin = 0;
		float speedMax = 0;
		float damping = 0;
		float angle = 0;
		float angleRange = 0;
		Color color;
	};

	class Emitter : public Actor
	{
	public:
		Emitter() = default;
		Emitter(const Transform& transform, const EmitterData& data, float lifespan = -1.0f) :
			Actor{ transform },
			m_data{ data }
		{
			m_lifespan = lifespan;
		}

		void Update(float dt);
		void Draw(neu::Renderer& renderer);

	private:
		void Emit();

	private:
		EmitterData m_data;
	};
}
