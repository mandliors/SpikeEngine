#pragma once

#include "UI/Widget/Widget.h"
#include "UI/Constraints/Constraint.h"

namespace Spike {

	class Panel : public Widget
	{
	public:
		Panel(const Color& backColor = Color(0, 128, 255, 255), uint8_t roundness = 0);
		~Panel();

		void Render() override;
	};
}