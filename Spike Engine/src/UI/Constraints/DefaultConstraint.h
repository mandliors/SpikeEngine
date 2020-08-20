#pragma once

#include "Constraint.h"

namespace Spike {

	class DefaultConstraint : public Constraint
	{
	public:
		DefaultConstraint(int x, int y, int w, int h)
		{
			m_X = x;
			m_Y = y;
			m_Z = w;
			m_W = h;
		}

		Vector2 CalculatePosition(IWidget* parent) override
		{
			return parent->GetPosition() + Vector2(m_X, m_Y);
		}

		Vector2 CalculateSize(IWidget* parent) override
		{
			return Vector2(m_Z, m_W);
		}
	};
}