#pragma once
#include "Vector2.h"
#include "Matrix22.h"

namespace neu
{
	class Transform
	{
	public:
		Vector2 position;
		float rotation = 0; //radians
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float rotation = 0, float scale = 1) :
			position { position },
			rotation { rotation },
			scale { scale }
		{}

		mat2 GetMatrix() const
		{
			mat2 Ms = mat2::CreateScale(scale);
			mat2 Mr = mat2::CreateRotation(rotation);

			return Ms * Mr;
		}
	};
}