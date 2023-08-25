#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"
#include "Core/Math/Rect.h"

namespace neu
{
	class SpriteRenderComponent : public RenderComponent
	{
	public:

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_texture->GetSize().Length() * 0.5f; }

		CLASS_DECLARATION(SpriteRenderComponent)

	public:
		Rect source;
		std::string textureName;
		res_t<Texture> m_texture;


	};
}
