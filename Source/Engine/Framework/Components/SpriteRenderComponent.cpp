#include "SpriteRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace neu
{
	CLASS_REGISTER(SpriteRenderComponent);

	bool SpriteRenderComponent::Initialize()
	{
		if(!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer);
		if (source.w == 0 && source.h == 0)
		{
			if (m_texture)
			{
				source.x = 0;
				source.y = 0;
				source.w = m_texture->GetSize().x;
				source.h = m_texture->GetSize().y;
			}
		}

		return true;
	}

	void SpriteRenderComponent::Update(float dt)
	{
		//
	}

	void SpriteRenderComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), source, m_owner->transform);
	}

	void SpriteRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, textureName);
		READ_DATA(value, source);
	}
}
