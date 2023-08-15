#include "SpriteRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace neu
{
	CLASS_REGISTER(SpriteRenderComponent);

	void SpriteRenderComponent::Update(float dt)
	{
		//
	}

	void SpriteRenderComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	}
}
