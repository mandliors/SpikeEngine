#pragma once

#include "Math/Vector2.h"
#include "UI/Widget/IWidget.h"
#include "Rendering/Color.h"
#include "UI/Constraints/Constraint.h"

namespace Spike {

	class Widget : public IWidget
	{
	public:
		virtual void SetBackColor(const Color& color);
		Constraint* GetConstraint();
		void SetConstraint(Constraint* constraint);
		virtual void Show() override;
		virtual void Hide() override;
		virtual void Update() override;
		virtual void Recalculate() override;
		virtual void Render() override;

	protected:
		Constraint* m_Constraint = nullptr;
		Color m_BackColor = Color(0, 128, 255, 255);
		Color m_BorderColor = Color::White();
	};
}