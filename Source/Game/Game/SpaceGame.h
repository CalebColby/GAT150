#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"

class SpaceGame : public neu::Game
{
public:

	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		PlayerDeadStart,
		GameOver,
		GameOverStart,
	};

public:
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(neu::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;
	size_t m_highScore = 0;

	float m_stateTimer = 0;

	std::shared_ptr<neu::Font> m_font;
	std::unique_ptr<neu::Text> m_scoreText;
	std::unique_ptr<neu::Text> m_titleText;
	std::unique_ptr<neu::Text> m_gameOverText;
	std::unique_ptr<neu::Text> m_livesText;
};