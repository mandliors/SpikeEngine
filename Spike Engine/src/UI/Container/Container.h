#pragma once

#include "UI/Constraints/Constraint.h"
#include "UI/Widget/Widget.h"
#include "UI/Widget/IWidget.h"
#include <vector>

namespace Spike {

	class Container : public IWidget
	{
	public:
		Container() = delete;
		Container(const Color& backColor = Color(60, 60, 60, 245), const Color& borderColor = Color::White(), uint32_t borderWidth = 1, uint8_t roundness = 0);
		~Container();

		template<typename T>
		T* Add(T* widget, Constraint* constraint)
		{
			widget->SetConstraint(constraint);
			widget->SetParent(this);
			m_Widgets.push_back(widget);
			return widget;
		}

		Constraint* GetConstraint();
		void SetConstraint(Constraint* constraint);

		void Show() override;
		void Hide() override;

		void Update() override;
		void Recalculate() override;
		void Render() override;

	private:
		std::vector<IWidget*> m_Widgets;
		Constraint* m_Constraint = nullptr;
		Color m_BackColor;
		Color m_BorderColor;
		bool m_Hidden = false;
		bool m_Focused = false;
		bool m_Hovering = false;
	};

}