#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Math/Vector2.h"
#include "Rendering/Renderer2D.h"
#include "Rendering/Color.h"

namespace Spike {

	struct Tag
	{
		std::string Name;

		Tag() = default;
		Tag(const Tag&) = default;
		Tag(std::string name)
			: Name(name) { }
	};

	struct Transform
	{
		Vector2 Position;
		Vector2 Size;
		int Rotation = 0;
		bool Active = true;

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const Vector2& position, const Vector2& size, int rotation)
			: Position(position), Size(size), Rotation(rotation) { }
	};

	struct SpriteRenderer
	{
		Color RenderColor = Color::White();
		std::string Path;

		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(const Color& color)
			: RenderColor(color) { }
		SpriteRenderer(const std::string& path, const Color& color = Color::White())
			: Path(path), RenderColor(color) { }
	};

	struct TextRenderer
	{
		Color RenderColor = Color::White();
		std::string Text;

		TextRenderer() = default;
		TextRenderer(const TextRenderer&) = default;
		TextRenderer(const std::string& text, const Color& color = Color::White())
			: Text(text), RenderColor(color) { }
	};
}