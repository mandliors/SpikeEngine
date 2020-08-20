#pragma once

#include <iostream>

namespace Spike
{
	struct Color
	{
		int R, G, B, A;
		Color()
			: R(0), G(0), B(0), A(0) { }
		Color(int r, int g, int b, int a = 255)
			: R(r), G(g), B(b), A(a) { }
		Color(const Color& other) = default;
		friend std::ostream& operator<<(std::ostream& stream, const Color& color);

		Color operator *(float mult);
		Color Multiply(float mult);
		
		static Color Black();
		static Color White();
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color Yellow();
		static Color Cyan();
		static Color Magenta();
		static Color Grey();
		static Color Purple();
		static Color Orange();
		static Color Transparent();
		static Color Random(bool alpha = true);
	};
}