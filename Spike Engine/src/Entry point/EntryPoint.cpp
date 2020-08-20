#include "Core/SpikeEngine.h"
#include "Game/Game.h"

#define UITest

int main(void)
{
	if (!Spike::Application::Init("Spike engine test", 1280, 720))
		Spike::Debug::Error("Error while initializing the application");
	else
		Spike::Debug::Grat("Successfully initialized the application");

	Game* game = new Game();
	game->Start();

	while (Spike::Application::IsRunning())
	{
		Spike::Application::Update();
		
		game->Update(Spike::Time::GetDeltaTime());

		Spike::Application::Render();
	}
	game->Exit();
	delete game;
	Spike::Application::Close();
}
