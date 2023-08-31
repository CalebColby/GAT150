#include "PlatformGame.h"

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool PlatformGame::Initialize()
{
	m_scene = std::make_unique<neu::Scene>();
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Load("Scenes/PlatformScene.json");
	m_scene->Initialize();

	neu::g_audioSystem.PlayOneShot("music", true); 

	return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
	m_scene->Update(dt);

	switch (m_state)
	{
	case PlatformGame::eState::Title:
	{
		
	}
		break;

	case PlatformGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll();
		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 2;
		if (m_lives <= 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case PlatformGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case PlatformGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			if (m_score > m_highScore)
			{
				m_highScore = m_score;
				std::string scoreString = std::to_string(m_highScore);
				neu::overwriteFile("HighScore.txt", scoreString);
			}
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
}

void PlatformGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void PlatformGame::OnAddPoints(const neu::Event& event)
{
}

void PlatformGame::OnPlayerDead(const neu::Event& event)
{
}
