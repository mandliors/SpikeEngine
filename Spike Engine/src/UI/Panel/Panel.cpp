#include "UI/Panel/Panel.h"
#include "Rendering/Renderer2D.h"

namespace Spike {

	Panel::Panel(const Color& backColor /*= Color(0, 128, 255, 255)*/, uint8_t roundness /*= 0*/)
	{
		m_BackColor = backColor;
		m_CornerRoundness = roundness;
	}

	Panel::~Panel()
	{
		delete m_Constraint;
	}

	void Panel::Render()
	{
		if (m_CornerRoundness == 0)
			Renderer2D::FillRect(m_Position.X, m_Position.Y, m_Size.X, m_Size.Y, m_BackColor);
		else
			Renderer2D::FillRoundedRect(m_Position.X, m_Position.Y, m_Size.X, m_Size.Y, m_CornerRoundness, m_BackColor);
	}
}