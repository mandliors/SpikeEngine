#include "Game.h"
#include "Core/SpikeEngine.h"

#ifdef UITest

using namespace Spike;


Button* button;
Container* container;
bool hidden = false;

void Game::Start()
{
	Application::SetMaxFPS(60);
	Application::EnableConsole();
	//Debug::SetLogLevel(Debug::LOG_LEVEL::_LOG_LEVEL_ENGINE);

	container = SpikeUI::AddContainer(new Container(Color::Grey(), Color::White()), new MarginConstraint(20, 20, 20, 20));
	button = container->Add(new Button("Button test", []()
		{
			Debug::Log(MessageBox::Show("Message box title", "Message box message"));
		}), new RelativeConstraint(0.6f, 0.6f));
}

void Game::Update(float dt)
{
	Application::Clear(0, 0, 0);

	if (Input::GetKeyDown(SDL_SCANCODE_T))
	{
		if (hidden)
			container->Show();
		else
			container->Hide();
		hidden = !hidden;
	}
}

void Game::Exit()
{

}

#endif