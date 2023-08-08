#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace neu
{
	void ModelRenderComponent::Update(float dt)
	{
		//
	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->m_transform);
	}
}