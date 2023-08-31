#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"

#include "PlatformGame.h"

#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>

using namespace std;


int main(int argc, char* argv[])
{
	INFO_LOG("Initializing Engine...");

	//Initialize Engine Systems
	neu::MemoryTracker::Initialize();
	neu::seedRandom((unsigned int)time(nullptr));
	neu::setFilePath("Assets/PlatformGame");

	neu::g_renderer.Initialize();
	neu::g_renderer.CreateWindow("GAT150", 800, 600);

	neu::g_inputSystem.Initialize();
	neu::g_audioSystem.Initialize();
	neu::PhysicsSystem::Instance().Initialize();
	INFO_LOG("Engine Initialized");

	neu::g_audioSystem.AddAudio("music", "Audio/FantasyFightMusic.mp3");

	auto game = make_unique<PlatformGame>();
	game->Initialize();

	INFO_LOG("Game Initialized");

	

	//main game loop
	bool quit = false;
	while (!quit)
	{
		//update Engine
		neu::g_Time.Tick();
		neu::g_inputSystem.Update();
		neu::g_audioSystem.Update();
		neu::g_particleSystem.Update(neu::g_Time.GetDeltaTime());
		neu::PhysicsSystem::Instance().Update(neu::g_Time.GetDeltaTime());
		if (neu::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) quit = true;

		//update Game
		game->Update(neu::g_Time.GetDeltaTime());

		//draw
		neu::g_renderer.SetColor(0, 0, 0, 0);
		neu::g_renderer.BeginFrame();

		game->Draw(neu::g_renderer);

		neu::g_particleSystem.Draw(neu::g_renderer);
		neu::g_renderer.EndFrame();
	}

	game->Shutdown();
	neu::g_renderer.Shutdown();

	return 0;
}