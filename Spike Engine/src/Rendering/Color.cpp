#include "Color.h"

namespace Spike {

	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		std::cout << "{" << color.R << ", " << color.G << ", " << color.B << "," << color.A << "}" << std::endl;
		return stream;
	}
	Color Color::Black()
	{
		Color col = Color(0, 0, 0, 0);
		return col;
	}
	Color Color::White()
	{
		Color col = Color(255, 255, 255, 255);
		return col;
	}
	Color Color::Red()
	{
		Color col = Color(255, 0, 0, 255);
		return col;
	}
	Color Color::Green()
	{
		Color col = Color(0, 255, 0, 255);
		return col;
	}
	Color Color::Blue()
	{
		Color col = Color(0, 0, 255, 255);
		return col;
	}
	Color Color::Yellow()
	{
		Color col = Color(255, 255, 0, 255);
		return col;
	}
	Color Color::Cyan()
	{
		Color col = Color(0, 255, 255, 255);
		return col;
	}
	Color Color::Magenta()
	{
		Color col = Color(255, 0, 255, 255);
		return col;
	}
}