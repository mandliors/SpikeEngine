#include "SpikeUI.h"

namespace Spike {

	std::vector<Container*> SpikeUI::s_Containers = std::vector<Container*>();
	Container* SpikeUI::m_MainContainer = nullptr;

	void SpikeUI::Init()
	{
		m_MainContainer = new Container(Color::Transparent(), Color::Transparent());
		m_MainContainer->SetParent(nullptr);
	}

	void SpikeUI::Update()
	{
		for (Container* container : s_Containers)
			container->Update();
	}

	void SpikeUI::Recalculate()
	{
		m_MainContainer->Recalculate();
		for (Container* container : s_Containers)
			container->Recalculate();
	}

	void SpikeUI::Render()
	{
		for (Container* container : s_Containers)
			container->Render();
	}

	void SpikeUI::Close()
	{
		for (Container* container : s_Containers)
			delete container;
	}
}