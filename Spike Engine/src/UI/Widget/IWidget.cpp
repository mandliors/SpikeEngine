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

	void IWidget::SetParent(IWidget* parent)
	{
		m_Parent = parent;
		Recalculate();
	}

	void IWidget::OnClick()
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnClick");
#endif
	}

	void IWidget::OnMouseEnter()
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnMouseEnter");
#endif
	}

	void IWidget::OnMouseHover()
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnMouseHover");
#endif
	}

	void IWidget::OnMouseLeave()
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnMouseLeave");
#endif
	}

	void IWidget::OnMousePressing()
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnMousePressing");
#endif
	}

	void IWidget::OnFocusEnter()
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnFocusEnter");
#endif
	}

	void IWidget::OnFocusLeave()
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnFocusLeave");
#endif
	}

	void IWidget::OnKeyDown(int key)
	{
#ifdef SPIKE_DEBUG
		if (!m_Hidden)
			Debug::__ENGINE_LOG("OnKeyDown: " + (char)SDL_GetKeyFromScancode((SDL_Scancode)key));
#endif
	}

}