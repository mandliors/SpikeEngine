#include "Game/Game.h"
#include "Core/SpikeEngine.h"

#ifdef UITest

using namespace Spike;

void Game::Start()
{
	Application::SetMaxFPS(60);
	Application::EnableConsole();
	//Debug::SetLogLevel(Debug::LOG_LEVEL::_LOG_LEVEL_ENGINE);

	Container* cont = SpikeUI::AddContainer(new Container(Color::Grey(), Color::White()), new MarginConstraint(20, 20, 20, 20));
	Button* button = cont->Add(new Button("Button test", nullptr), new RelativeConstraint(0.6f, 0.6f));
 }

void Game::Update(float dt)
{

}

void Game::Exit()
{

}

#endif