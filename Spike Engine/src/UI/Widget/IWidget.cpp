#include "IWidget.h"
#include "Debug/Debug.h"

namespace Spike {

	Vector2 IWidget::GetPosition()
	{
		return m_Position;
	}

	Vector2 IWidget::GetSize()
	{
		return m_Size;
	}

	IWidget* IWidget::GetParent()
	{
		return m_Parent;
	}

	void IWidget::SetPosition(const Vector2& position)
	{
		m_Position = position;
	}

	void IWidget::SetSize(const Vector2& size)
	{
		m_Size = size;
	}

	void IWidget::SetParent(IWidget* parent)
	{
		m_Parent = parent;
		Recalculate();
	}

	void IWidget::OnClick()
	{
#ifdef SPIKE_DEBUG
		Debug::_EngineLog("OnClick");
#endif
	}

	void IWidget::OnMouseEnter()
	{
#ifdef SPIKE_DEBUG
		Debug::_EngineLog("OnMouseEnter");
#endif
	}

	void IWidget::OnMouseHover()
	{
#ifdef SPIKE_DEBUG
		Debug::_EngineLog("OnMouseHover");
#endif
	}

	void IWidget::OnMouseLeave()
	{
#ifdef SPIKE_DEBUG
		Debug::_EngineLog("OnMouseLeave");
#endif
	}

	void IWidget::OnMousePressing()
	{
#ifdef SPIKE_DEBUG
		Debug::_EngineLog("OnMousePressing");
#endif
	}

	void IWidget::OnFocusEnter()
	{
#ifdef SPIKE_DEBUG
		Debug::_EngineLog("OnFocusEnter");
#endif
	}

	void IWidget::OnFocusLeave()
	{
#ifdef SPIKE_DEBUG
		Debug::_EngineLog("OnFocusLeave");
#endif
	}

	void IWidget::OnKeyDown(int key)
	{
#ifdef SPIKE_DEBUG
		Debug::_EngineLog("OnKeyDown: " + (char)SDL_GetKeyFromScancode((SDL_Scancode)key));
#endif
	}

}