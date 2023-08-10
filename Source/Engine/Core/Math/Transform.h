#pragma once
#include "Vector2.h"
#include "Matrix33.h"

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

		mat3 GetMatrix() const
		{
			mat3 Ms = mat3::CreateScale(scale);
			mat3 Mr = mat3::CreateRotation(rotation);
			mat3 Mt = mat3::CreateTranslation(position);
			mat3 Mx = Mt * Ms * Mr;

			return Mx;
		}
	};
}