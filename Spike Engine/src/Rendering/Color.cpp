#include "Color.h"

namespace Spike {

	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		std::cout << "{" << color.R << ", " << color.G << ", " << color.B << "," << color.A << "}" << std::endl;
		return stream;
	}
	Color Color::Black()
	{
		return Color(0, 0, 0, 0);
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
	Color Color::Random(bool alpha)
	{
		return Color(rand() % 256, rand() % 256, rand() % 256, alpha ? rand() % 256 : 255);
	}
}