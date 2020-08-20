#pragma once

#include "Constraint.h"

namespace Spike {

	class RelativeConstraint : public Constraint
	{
	public:
		RelativeConstraint(float x, float y, float w, float h)
		{
			m_X = x;
			m_Y = y;
			m_Z = w;
			m_W = h;
		}

		RelativeConstraint(float w, float h)
		{
			m_X = (1 - w) / 2.0f;
			m_Y = (1 - h) / 2.0f;
			m_Z = w;
			m_W = h;
		}

		Vector2 CalculatePosition(IWidget* parent) override
		{
			return parent->GetPosition() + Vector2(parent->GetSize().X * m_X, parent->GetSize().Y * m_Y);
		}

		Vector2 CalculateSize(IWidget* parent) override
		{
			return parent->GetSize() * Vector2(m_Z, m_W);
		}
	};

}