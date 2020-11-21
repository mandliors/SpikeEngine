#include "Color.h"
#include "Math/Math.h"

namespace Spike {

	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		std::cout << "{" << color.R << ", " << color.G << ", " << color.B << ", " << color.A << "}" << std::endl;
		return stream;
	}
	Color Color::Black()
	{
		return Color(0, 0, 0, 255);
	}
	Color Color::White()
	{
		return Color(255, 255, 255, 255);
	}
	Color Color::Red()
	{
		return Color(255, 0, 0, 255);
	}
	Color Color::Green()
	{
		return Color(0, 255, 0, 255);
	}
	Color Color::Blue()
	{
		return Color(0, 0, 255, 255);
	}
	Color Color::Yellow()
	{
		return Color(255, 255, 0, 255);
	}
	Color Color::Cyan()
	{
		return Color(0, 255, 255, 255);;
	}
	Color Color::Magenta()
	{
		return Color(255, 0, 255, 255);
	}

	Color Color::Grey()
	{
		return Color(128, 128, 128, 255);
	}

	Color Color::Purple()
	{
		return Color(76, 0, 153, 255);
	}

	Color Color::Orange()
	{
		return Color(204, 102, 0, 255);
	}

	Color Color::Transparent()
	{
		return Color(0, 0, 0, 0);
	}

	Color Color::Random(bool alpha)
	{
		return Color(rand() % 256, rand() % 256, rand() % 256, alpha ? rand() % 256 : 255);
	}

	Color Color::operator*(float mult)
	{
		if (mult < 1.0f)
			return Color(R * mult, G * mult, B * mult, A);
		else
			return Color(R + (255 - R) * (mult - 1.0f), G + (255 - G) * (mult - 1.0f), B + (255 - B) * (mult - 1.0f), A);
	}

	Color Color::Multiply(float mult)
	{
		return *this * mult;
	}
}