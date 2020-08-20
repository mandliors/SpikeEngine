#pragma once

#include "UI/Widget/Widget.h"
#include "UI/Constraints/Constraint.h"
#include <string>

namespace Spike {

	class Button : public Widget
	{
	public:
		Button() = delete;
		Button(const std::string& text, void(*func)() = nullptr, const Color& backColor = Color(0, 128, 255, 255), const Color& borderColor = Color::White(), uint32_t borderWidt = 1, uint8_t roundness = 0);
		~Button();

		void OnClick() override;
		void Render() override;

	private:
		void(*m_ClickFunc)() = nullptr;
		Color m_HoverColor;
		Color m_PressColor;
		Color m_ForegroundColor;
	};

}