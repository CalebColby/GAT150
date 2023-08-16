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

		bool Initialize() override;
		virtual void Update(float dt) override;
		virtual void Draw(Renderer& renderer) override;
		virtual float GetRadius() override { return m_model->GetRadius(); }

		CLASS_DECLARATION(ModelRenderComponent)

	public:
		std::string modelName;
		res_t<Model> m_model;
	};
}