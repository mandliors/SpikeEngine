#include "Button.h"
#include "Rendering/Renderer2D.h"
#include "Debug/Debug.h"

namespace Spike {

	Button::Button(const std::string& text, void(*func)(), 
				   const Color& backColor,
				   const Color& borderColor,
				   const Color& foreColor, uint32_t borderWidth, uint8_t roundness)
	{
		m_Text = text;
		m_ClickFunc = func;
		m_BackColor = backColor;
		m_BorderColor = borderColor;
		m_HoverColor = m_BackColor * 1.1f;
		m_PressColor = m_BackColor * 1.2f;
		m_ForegroundColor = foreColor;
		m_BorderWidth = borderWidth;
		m_CornerRoundness = roundness;
	}

	Button::~Button()
	{
		delete m_Constraint;
	}

	void Button::OnClick()
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnClick");
#endif
		if (m_ClickFunc != nullptr)
			m_ClickFunc();
	}

	void Button::Render()
	{
		if (!m_Hidden)
		{
			//draw interior
			if (m_Pressing) Renderer2D::FillRoundedRect(m_Position.X, m_Position.Y, m_Size.X, m_Size.Y, m_CornerRoundness, m_PressColor);
			else if (m_Hovering) Renderer2D::FillRoundedRect(m_Position.X, m_Position.Y, m_Size.X, m_Size.Y, m_CornerRoundness, m_HoverColor);
			else Renderer2D::FillRoundedRect(m_Position.X, m_Position.Y, m_Size.X, m_Size.Y, m_CornerRoundness, m_BackColor);

			//draw border
			for (size_t i = 0; i < m_BorderWidth; i++)
				Renderer2D::DrawRoundedRect(m_Position.X + i, m_Position.Y + i, m_Size.X + 1 - 2 * i, m_Size.Y + 1 - 2 * i, m_CornerRoundness, m_BorderColor);
		
			//render text
			Renderer2D::SetTextAlign(SpikeTextAlign::CENTER, SpikeTextAlign::CENTER);
			Renderer2D::RenderText(m_Text, m_Position.X + (float)m_Size.X * 0.5f, m_Position.Y + (float)m_Size.Y * 0.5f, m_ForegroundColor, true);
		}
	}
}