#pragma once
#include "Framework/Resource/Resource.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Transform.h"
#include "Core/Math/Color.h"
#include <vector>

namespace neu
{
	class Renderer;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		bool Load(const std::string& fileName);
		bool Create(std::string filename, ...) override;

		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();

	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}