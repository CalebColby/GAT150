#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"

#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>

using namespace std;

class Star
{
public:
	Star(const neu::Vector2 pos, const neu::Vector2 vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(const float dt)
	{
		m_pos += m_vel * dt;

		if (m_pos.x >= neu::g_renderer.GetWidth()) { m_pos.x = 0; }
		if (m_pos.y >= neu::g_renderer.GetHeight()) { m_pos.y = 0; }
	}

public:
	neu::Vector2 m_pos;
	neu::Vector2 m_vel;
};


int main(int argc, char* argv[])
{

	INFO_LOG("Initialize Engine");

	//Initialize Engine Systems
	neu::MemoryTracker::Initialize();
	neu::seedRandom((unsigned int)time(nullptr));
	neu::setFilePath("Assets");
	
	neu::g_renderer.Initialize();
	neu::g_renderer.CreateWindow("GAT150", 800,600);

	neu::g_inputSystem.Initialize();
	neu::g_audioSystem.Initialize();
	neu::PhysicsSystem::Instance().Initialize();

	auto game = make_unique<SpaceGame>();
	game->Initialize();

	std::vector<Star> stars;
	for (size_t i = 0; i < 1000; i++)
	{
		neu::Vector2 pos(neu::randomf((float)neu::g_renderer.GetWidth()), neu::randomf((float)neu::g_renderer.GetHeight()));
		neu::Vector2 vel(neu::randomf(100,400), neu::randomf(-200, 200));

		stars.push_back(Star(pos, vel));
	}

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//update Engine
		neu::g_Time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();
		neu::g_particleSystem.Update(neu::g_Time.GetDeltaTime());
		if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) quit = true;

		//update Game
		game->Update(neu::g_Time.GetDeltaTime());

		//draw
		neu::g_renderer.SetColor(0, 0, 0, 0);
		neu::g_renderer.BeginFrame();

		game->Draw(neu::g_renderer);
		for (auto& star : stars) 
		{
			star.Update(neu::g_Time.GetDeltaTime());

			neu::g_renderer.SetColor(neu::random(256), neu::random(256), neu::random(256), 255);
			neu::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		neu::g_particleSystem.Draw(neu::g_renderer);
		neu::g_renderer.EndFrame();
	}

	stars.clear();
	game->Shutdown();
	neu::g_renderer.Shutdown();

	return 0;
}