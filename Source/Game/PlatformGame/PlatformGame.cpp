#include "PlatformGame.h"

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool PlatformGame::Initialize()
{
	m_scene = std::make_unique<neu::Scene>();
	m_scene->Load("Scenes/PlatformScene.json");
	m_scene->Initialize();

	return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
	m_scene->Update(dt);
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
