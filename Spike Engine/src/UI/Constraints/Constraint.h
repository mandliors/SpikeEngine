#pragma once

#include "Math/Vector2.h"
#include "UI/Widget/IWidget.h"

namespace Spike {

	class Constraint
	{
	public:
		virtual Vector2 CalculatePosition(IWidget* parent)
		{
			return Vector2::Empty();
		}
		virtual Vector2 CalculateSize(IWidget* parent)
		{
			return Vector2::Empty();
		}

	protected:
		float m_X;
		float m_Y;
		float m_Z;
		float m_W;
	};
}