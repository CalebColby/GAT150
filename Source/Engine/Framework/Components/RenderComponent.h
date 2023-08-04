#pragma once
#include "Component.h"

namespace neu
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	protected:

	};
}