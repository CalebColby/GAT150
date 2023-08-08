#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace neu
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
		ModelRenderComponent() = default;
		~ModelRenderComponent() = default;

		virtual void Update(float dt) override;
		virtual void Draw(Renderer& renderer) override;

	public:
		res_t<Model> m_model;
	};
}