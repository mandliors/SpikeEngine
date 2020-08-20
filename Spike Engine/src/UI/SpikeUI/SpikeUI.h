#pragma once

#include "UI/Widget/IWidget.h"
#include "UI/Constraints/Constraint.h"
#include "UI/Constraints/DefaultConstraint.h"
#include "UI/Constraints/MarginConstraint.h"
#include "UI/Constraints/RelativeConstraint.h"
#include "UI/Container/Container.h"
#include "UI/Panel/Panel.h"
#include "UI/Button/Button.h"
#include "Rendering/Renderer2D.h"
#include <vector>

namespace Spike {

	class SpikeUI
	{
	public:
		SpikeUI() = delete;
		
		static Container* AddContainer(Container* container, Constraint* constraint)
		{
			container->SetConstraint(constraint);
			container->SetParent(m_MainContainer);
			s_Containers.push_back(container);
			return container;
		}

		static void Init();
		static void Update();
		static void Recalculate();
		static void Render();
		static void Close();

	private:
		static std::vector<Container*> s_Containers;
		static Container* m_MainContainer;
	};

}