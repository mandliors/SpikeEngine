#pragma once

#include "Constraint.h"

namespace Spike {

	class MarginConstraint : public Constraint
	{
	public:
		MarginConstraint(int left, int right, int top, int bottom)
		{
			m_X = left;
			m_Y = right;
			m_Z = top;
			m_W = bottom;
		}

		Vector2 CalculatePosition(IWidget* parent) override
		{
			return parent->GetPosition() + Vector2(m_X, m_Z);
		}

		Vector2 CalculateSize(IWidget* parent) override
		{
			return parent->GetSize() - Vector2(m_X + m_Y, m_Z + m_W);
		}
	};

}