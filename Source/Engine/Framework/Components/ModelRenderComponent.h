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
		virtual float GetRadius() override { return m_model->GetRadius(); }

		CLASS_DECLARATION(ModelRenderComponent);

	public:
		res_t<Model> m_model;
	};
}