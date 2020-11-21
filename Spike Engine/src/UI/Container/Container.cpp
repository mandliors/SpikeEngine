#include "UI/Container/Container.h"
#include "Core/Application.h"

namespace Spike {

	Container::Container(const Color& backColor, const Color& borderColor, uint32_t borderWidth, uint8_t roundness)
	{
		m_BackColor = backColor;
		m_BorderColor = borderColor;
		m_Position = Vector2(0, 0);
		m_Size = Vector2(0, 0);
		m_BorderWidth = borderWidth;
		m_CornerRoundness = roundness;
	}

	Container::~Container()
	{
		for (IWidget* widget : m_Widgets) 
			delete widget;
		m_Widgets.clear();
		if (m_Constraint != nullptr)
			delete m_Constraint;
	}

	Constraint* Container::GetConstraint()
	{
		return m_Constraint;
	}

	void Container::SetConstraint(Constraint* constraint)
	{
		if (m_Constraint != nullptr)
			delete m_Constraint;
		m_Constraint = constraint;
		Recalculate();
	}

	void Container::Show()
	{
		m_Hidden = false;
		for (IWidget* widget : m_Widgets)
			widget->Show();
	}

	void Container::Hide()
	{
		m_Hidden = true;
		for (IWidget* widget : m_Widgets)
			widget->Hide();
	}

	void Container::Update()
	{
		for (IWidget* widget : m_Widgets)
			widget->Update();
	}

	void Container::Recalculate()
	{
		if (m_Parent == nullptr)
		{
			m_Position = Vector2(0, 0);
			m_Size = Application::GetWindowSize();
		}
		else
		{
			m_Position = m_Constraint->CalculatePosition(m_Parent);
			m_Size = m_Constraint->CalculateSize(m_Parent);
		}

		for(IWidget* widget : m_Widgets)
			widget->Recalculate();
	}

	void Container::Render()
	{
		if (!m_Hidden)
		{
			if (m_Parent != nullptr)
			{
				//draw interior
				Renderer2D::FillRoundedRect(m_Position.X, m_Position.Y, m_Size.X, m_Size.Y, m_CornerRoundness, m_BackColor);

				//draw border
				for (size_t i = 0; i < m_BorderWidth; i++)
					Renderer2D::DrawRoundedRect(m_Position.X + i, m_Position.Y + i, m_Size.X + 1 - 2 * i, m_Size.Y + 1 - 2 * i, m_CornerRoundness, m_BorderColor);
			}
			for (IWidget* widget : m_Widgets)
				widget->Render();
		}
	}

}