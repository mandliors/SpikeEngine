#include "Widget.h"
#include "Input/Input.h"
#include "Math/Math.h"

namespace Spike {

	Constraint* Widget::GetConstraint()
	{
		return m_Constraint;
	}

	void Widget::SetConstraint(Constraint* constraint)
	{
		if (m_Constraint != nullptr)
			delete m_Constraint;
		m_Constraint = constraint;
		Recalculate();
	}

	void Widget::Show()
	{
		m_Hidden = false;
	}

	void Widget::Hide()
	{
		m_Hidden = true;
	}

	void Widget::Update()
	{
		//mouse click, focus
		if (Input::GetMouseButtonUp(0))
		{
			if (Utility::OverlapPoint(Input::GetMousePosition(), m_Position, m_Size))
			{
				if (!m_Focused) OnFocusEnter();
				m_Focused = true;
				OnClick();
			}
			else if (m_Focused) { m_Focused = false; OnFocusLeave(); }
		}
		//mouse movement
		if (Utility::OverlapPoint(Input::GetMousePosition(), m_Position, m_Size))
		{
			if (m_Hovering) OnMouseHover();
			else { m_Hovering = true; OnMouseEnter(); OnMouseHover(); }
		}
		else
			if (m_Hovering) { m_Hovering = false; OnMouseLeave(); }
		//keyboard
		if (m_Focused)
		{
			std::vector<int> keysDown = Input::GetKeysDown();
			if (keysDown.size() != 0)
				for (int i : keysDown) OnKeyDown(i);
		}
		//mouse press
		if (Input::GetMouseButton(0) && m_Hovering)
		{
			m_Pressing = true;
			OnMousePressing();
		}
		else m_Pressing = false;
	}

	void Widget::Recalculate()
	{
		if (m_Parent != nullptr)
		{
			m_Position = m_Constraint->CalculatePosition(m_Parent);
			m_Size = m_Constraint->CalculateSize(m_Parent);
		}
	}

	void Widget::Render()
	{
		std::cout << "Render" << std::endl;
	}
}