#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool SpaceGame::Initialize()
{// create font / text objects
	m_font = GET_RESOURCE(neu::Font, "SpaceGame/Fonts/PaladinFLF.ttf", 24);
	m_scoreText = std::make_unique<neu::Text>(m_font);
	m_scoreText->Create(neu::g_renderer, "SCORE 0000", neu::Color{ 1, 1, 1, 1 });

	//m_titleText = std::make_unique<neu::Text>(m_font);
	//m_titleText->Create(neu::g_renderer, "Star Field", neu::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<neu::Text>(m_font);
	m_gameOverText->Create(neu::g_renderer, "Game Over", neu::Color{ 1, 1, 1, 1 });

	m_livesText = std::make_unique<neu::Text>(m_font);
	m_livesText->Create(neu::g_renderer, "X Lives Left", neu::Color{ 1, 1, 1, 1 });

	//Load HighScore
	std::string buffer;
	neu::readFile("SpaceGame/HighScore.txt", buffer);
	m_highScore = static_cast<size_t>(std::stoi(buffer));


	// load audio
	neu::g_audioSystem.AddAudio("hit", "SpaceGame/Audio/Explosion.wav");
	neu::g_audioSystem.AddAudio("laser", "SpaceGame/Audio/Laser_Fire.wav");
	neu::g_audioSystem.AddAudio("PowerUp", "SpaceGame/Audio/Powerup.wav");
	neu::g_audioSystem.AddAudio("music", "SpaceGame/Audio/Music.mp3");

	neu::g_audioSystem.PlayOneShot("music", true);

	// create scene
	m_scene = std::make_unique<neu::Scene>();
	m_scene->Load("SpaceGame/Scenes/SpaceScene.json");
	m_scene->Initialize();

	m_scene->GetActorByName("Title")->active = true;
	m_state = eState::Title;

	//add events
	EVENT_SUBSCRIBE("OnAddPoints", SpaceGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);
	//neu::EventManager::Instance().Subscribe("OnAddPoints", this, std::bind(&SpaceGame::OnAddPoints, this, std::placeholders::_1));
	//neu::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&SpaceGame::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		m_scene->GetActorByName("Title")->active = true;
		if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_scene->GetActorByName("Title")->active = false;
			m_state = eState::StartGame;
		}
		break;

	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
		{
			auto player = INSTANTIATE(Player, "Player");
			player->Initialize();
			m_scene->Add(std::move(player));
		}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			//auto enemy = std::make_unique<Enemy>(neu::randomf(75.0f, 150.0f), neu::Pi, neu::Transform{ { neu::random(neu::g_renderer.GetWidth()), neu::random(neu::g_renderer.GetHeight()) }, neu::randomf(neu::TwoPi), 0.5f});
			auto enemy = INSTANTIATE(Enemy, "Enemy");

			enemy->transform.position = { neu::random(neu::g_renderer.GetWidth()), neu::random(neu::g_renderer.GetHeight()) };
			enemy->transform.rotation = neu::randomf(neu::TwoPi);

			enemy->tag = "Enemy";
			enemy->m_game = this;

			enemy->Initialize();

			m_scene->Add(std::move(enemy));
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 2;
		if (m_lives <= 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
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
	
	//m_scoreText->Create(neu::g_renderer, ((m_state == eState::Title) ? "High Score: " + std::to_string(m_highScore) : "Score: " + std::to_string(m_score)), 
		//{1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(neu::Renderer& renderer)
{
	m_scene->Draw(renderer);
	if (m_state == eState::Title)
	{
		//m_titleText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::GameOver)
	{
		m_gameOverText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::PlayerDead)
	{
		m_livesText->Create(neu::g_renderer, ((m_lives == 1) ? "1 Life Remaining" : std::to_string(m_lives) + " Lives Remaining"), 
			{ 1, 1, 1, 1 });
		m_livesText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 10, 10);
}

void SpaceGame::OnAddPoints(const neu::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const neu::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
