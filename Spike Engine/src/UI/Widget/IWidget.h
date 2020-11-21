#pragma once

#pragma once

#include "Math/Vector2.h"
#include "Rendering/Color.h"

namespace Spike {

	class IWidget
	{
	public:
		virtual Vector2 GetPosition();
		virtual Vector2 GetSize();
		virtual IWidget* GetParent();
		virtual void SetParent(IWidget* parent);
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void Update() = 0;
		virtual void Recalculate() = 0;
		virtual void Render() = 0;
	protected:
		//Events
		virtual void OnClick();
		virtual void OnMouseEnter();
		virtual void OnMouseHover();
		virtual void OnMouseLeave();
		virtual void OnMousePressing();
		virtual void OnFocusEnter();
		virtual void OnFocusLeave();
		virtual void OnKeyDown(int key);

		Vector2 m_Position = Vector2::Empty();
		Vector2 m_Size = Vector2::Empty();
		IWidget* m_Parent = nullptr;
		uint8_t m_CornerRoundness = 0;
		uint32_t m_BorderWidth = 1;
		bool m_Hidden = false;
		bool m_Focused = false;
		bool m_Hovering = false;
		bool m_Pressing = false;
	};
}