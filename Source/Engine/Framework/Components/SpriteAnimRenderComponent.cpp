#include "SpriteAnimRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Resource/ResourceManager.h"

namespace neu
{
	CLASS_REGISTER(SpriteAnimRenderComponent);

	bool SpriteAnimRenderComponent::Initialize()
	{
		SpriteRenderComponent::Initialize();

		SetSequence(defaultSequenceName);
		UpdateSource();

		return true;
	}

	void SpriteAnimRenderComponent::Update(float dt)
	{
		frameTimer -= dt;
		if (frameTimer <= 0)
		{
			frameTimer = 1.0f / m_sequence->fps;
			frame++;
			if (frame > m_sequence->endFrame)
			{
				frame = (m_sequence->loop) ? m_sequence->startFrame : m_sequence->endFrame;
			}
		}

		UpdateSource();
	}

	void SpriteAnimRenderComponent::SetSequence(const std::string& sequenceName, bool force)
	{
		if (m_sequence && m_sequence->name == sequenceName && !force) return;

		if (m_sequences.find(sequenceName) != m_sequences.end())
		{
			m_sequence = &m_sequences[sequenceName];
			if (m_sequence->texture) m_texture = m_sequence->texture;
			frame = m_sequence->startFrame;
			frameTimer = 1.0f / m_sequence->fps;
		}
	}

	void SpriteAnimRenderComponent::UpdateSource()
	{
		if (!m_texture) return;

		vec2 cellSize = m_texture->GetSize() / vec2{m_sequence->numColumns, m_sequence->numRows};
		int column = (frame - 1) % m_sequence->numColumns;
		int row = (frame - 1) % m_sequence->numRows;

		source.x = (int)(column * cellSize.x);
		source.y = (int)(row * cellSize.y);
		source.h = (int)(cellSize.x);
		source.w = (int)(cellSize.y);
	}

	void SpriteAnimRenderComponent::Read(const json_t& value)
	{
		SpriteRenderComponent::Read(value);

		// read in animation sequences
		if (HAS_DATA(value, sequences) && GET_DATA(value, sequences).IsArray())
		{
			for (auto& sequenceValue : GET_DATA(value, sequences).GetArray())
			{
				AnimSequence sequence;

				READ_NAME_DATA(sequenceValue, "name", sequence.name);
				READ_NAME_DATA(sequenceValue, "fps", sequence.fps);
				READ_NAME_DATA(sequenceValue, "numColumns", sequence.numColumns);
				READ_NAME_DATA(sequenceValue, "numRows", sequence.numRows);
				READ_NAME_DATA(sequenceValue, "startFrame", sequence.startFrame);
				READ_NAME_DATA(sequenceValue, "endFrame", sequence.endFrame);

				// read texture
				std::string textureName;
				READ_DATA(sequenceValue, textureName);
				sequence.texture = GET_RESOURCE(Texture, textureName, g_renderer);

				m_sequences[sequence.name] = sequence;
			}
		}

		if (!READ_DATA(value, defaultSequenceName))
		{
			// if default sequence not specified, use the first sequence in the sequences map
			defaultSequenceName = m_sequences.begin()->first;
		}
	}
}