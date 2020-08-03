#pragma once

#include <iostream>

namespace Spike
{
	struct Color
	{
		float R, G, B, A;
		Color()
			: R(0), G(0), B(0), A(0) { }
		Color(float r, float g, float b, float a = 255)
			: R(r), G(g), B(b), A(a) { }
		Color(const Color& other) = default;
		friend std::ostream& operator<<(std::ostream& stream, const Color& color);

		static Color Black();
		static Color White();
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color Yellow();
		static Color Cyan();
		static Color Magenta();
	};
}