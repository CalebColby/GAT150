#pragma once

#include "SpriteRenderComponent.h"
#include <map>

namespace neu
{
	class SpriteAnimRenderComponent : public SpriteRenderComponent
	{
	public:
		struct AnimSequence
		{
			std::string name;

			float fps = 0;
			int numColumns = 0;
			int numRows = 0;

			int startFrame = 0;
			int endFrame = 0;

			bool loop = true;

			std::shared_ptr<Texture> texture;
		};

	public:
		CLASS_DECLARATION(SpriteAnimRenderComponent)

		bool Initialize() override;
		void Update(float dt) override;

		void SetSequence(const std::string& sequenceName, bool update = true, bool force = false);
		void SetSequence(const std::string& sequenceName, const std::string& nextSequneceName, bool update = true, bool force = false);
		void UpdateSource();

	public:
		int frame = 0;
		float frameTimer = 0;

	private:
		std::string defaultSequenceName;
		std::map<std::string, AnimSequence> m_sequences;
		AnimSequence* m_sequence = nullptr;
	};
}