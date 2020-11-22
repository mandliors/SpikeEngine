#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Primitives/SDL2_gfxPrimitives.h"
#include "Color.h"
#include "Math/Vector2.h"
#include <string>

namespace Spike
{
	enum class SpikeTextAlign
	{
		LEFT = 0, CENTER = 1, RIGHT = 2, TOP = 0, BOTTOM = 2
	};

	enum class SpikeTextRenderMode
	{
		NORMAL = 0, ANTIALIASED
	};

	class Renderer2D
	{
	public:
		Renderer2D() = delete;
		~Renderer2D() { s_Renderer = nullptr; }
		static bool Init(SDL_Window* win, int idx, Uint32 flags);
		static void Close() { TTF_CloseFont(s_Font); }
		static SDL_Renderer* GetRenderer();
		static void Clear(int r, int g, int b, int a = 255);
		static void Clear(const Color& color);
		static void EnableAntiAliasing(bool v = true);
		static void DisableAntiAlising();
		static void PutPixel(int x, int y, int r = 255, int g = 255, int b = 255, int a = 255);
		static void PutPixel(int x, int y, const Color& color);
		static void DrawLine(int x1, int y1, int x2, int y2, int r = 255, int g = 255, int b = 255, int a = 255);
		static void DrawLine(int x1, int y1, int x2, int y2, const Color& color);
		static void DrawRect(int x, int y, int w, int h, int r = 255, int g = 255, int b = 255, int a = 255);
		static void DrawRect(int x, int y, int w, int h, const Color& color);
		static void FillRect(int x, int y, int w, int h, int r = 255, int g = 255, int b = 255, int a = 255);
		static void FillRect(int x, int y, int w, int h, const Color& color);
		static void DrawRoundedRect(int x, int y, int w, int h, int rad, int r = 255, int g = 255, int b = 255, int a = 255);
		static void DrawRoundedRect(int x, int y, int w, int h, int rad, const Color& color);
		static void FillRoundedRect(int x, int y, int w, int h, int rad, int r = 255, int g = 255, int b = 255, int a = 255);
		static void FillRoundedRect(int x, int y, int w, int h, int rad, const Color& color);
		static void DrawCircle(int x, int y, int rad, int r = 255, int g = 255, int b = 255, int a = 255);
		static void DrawCircle(int x, int y, int rad, const Color& color);
		static void FillCircle(int x, int y, int rad, int r = 255, int g = 255, int b = 255, int a = 255);
		static void FillCircle(int x, int y, int rad, const Color& color);
		static void DrawEllipse(int x, int y, int w, int h, int r = 255, int g = 255, int b = 255, int a = 255);
		static void DrawEllipse(int x, int y, int w, int h, const Color& color);
		static void FillEllipse(int x, int y, int w, int h, int r = 255, int g = 255, int b = 255, int a = 255);
		static void FillEllipse(int x, int y, int w, int h, const Color& color);
		static void DrawTrigon(int x1, int y1, int x2, int y2, int x3, int y3, int r = 255, int g = 255, int b = 255, int a = 255);
		static void DrawTrigon(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color);
		static void FillTrigon(int x1, int y1, int x2, int y2, int x3, int y3, int r = 255, int g = 255, int b = 255, int a = 255);
		static void FillTrigon(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color);
		static void DrawPolygon(Sint16* x, Sint16* y, int n, int r = 255, int g = 255, int b = 255, int a = 255);
		static void DrawPolygon(Sint16* x, Sint16* y, int n, const Color& color);
		static void FillPolygon(Sint16* x, Sint16* y, int n, int r = 255, int g = 255, int b = 255, int a = 255);
		static void FillPolygon(Sint16* x, Sint16* y, int n, const Color& color);
		static void DrawRotatedRect(int x, int y, int w, int h, int angle, int r = 255, int g = 255, int b = 255, int a = 255);
		static void DrawRotatedRect(int x, int y, int w, int h, int angle, const Color& color = Color::White());
		static void FillRotatedRect(int x, int y, int w, int h, int angle, int r = 255, int g = 255, int b = 255, int a = 255);
		static void FillRotatedRect(int x, int y, int w, int h, int angle, const Color& color);
		static void SetFont(const std::string& path, int size);
		static void SetFontStyle(int style);
		static void SetFontOutline(int thickness);
		static void SetTextAlign(SpikeTextAlign horizontal, SpikeTextAlign vertical = SpikeTextAlign::TOP);
		static void SetFontHinting(int hinting);
		static void SetFontKerning(bool kerning);
		static void SetTextRenderMode(SpikeTextRenderMode renderMode);
		static void RenderText(const std::string& text, int x, int y, int r = 255, int g = 255, int b = 255, int a = 255);
		static void RenderText(const std::string& text, int x, int y, int r, int g, int b, int a, bool anti_aliasing);
		static void RenderText(const std::string& text, int x, int y, const Color& color);
		static void RenderText(const std::string& text, int x, int y, const Color& color, bool anti_aliasing);
		static void RenderRotatedText(const std::string& text, int x, int y, int angle, int r = 255, int g = 255, int b = 255, int a = 255);
		static void RenderRotatedText(const std::string& text, int x, int y, int angle, int r, int g, int b, int a, bool anti_aliasing);
		static void RenderRotatedText(const std::string& text, int x, int y, int angle, const Color& color);
		static void RenderRotatedText(const std::string& text, int x, int y, int angle, const Color& color, bool anti_aliasing);
		static void RenderTexture(SDL_Texture* texture, const Vector2& position, const Vector2& size, const Color& color = Color::White());
		static void RenderRotatedTexture(SDL_Texture* texture, const Vector2& position, const Vector2& size, int angle, const Color& color = Color::White());

	private:
		static SDL_Renderer* s_Renderer;
		static bool s_AntiAliasing;
		static TTF_Font* s_Font;
		static float s_HorizontalAlignmentMultiplier;
		static float s_VerticalAlignmentMultiplier;
		static SpikeTextRenderMode s_TextRenderMode;
	};
}