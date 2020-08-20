#include "Renderer2D.h"

namespace Spike {

	SDL_Renderer* Renderer2D::s_Renderer = nullptr;
	bool Renderer2D::s_AntiAliasing = false;
	TTF_Font* Renderer2D::s_Font = nullptr;

	bool Renderer2D::Init(SDL_Window* win, int idx, Uint32 flags)
	{
		bool success = true;
		s_Renderer = SDL_CreateRenderer(win, idx, flags);
		if (TTF_Init() == -1)
			success = false;
		s_Font = TTF_OpenFont("assets/arial.ttf", 24);
		//s_Font = TTF_OpenFont("assets/FreeMono.ttf", 24);
		if (!s_Font)
			success = false;
		return success;
	}
	SDL_Renderer* Renderer2D::GetRenderer()
	{
		return s_Renderer;
	}
	void Renderer2D::Clear(int r, int b, int g, int a)
	{
		SDL_SetRenderDrawColor(s_Renderer, r, g, b, a);
		SDL_RenderClear(s_Renderer);
	}
	void Renderer2D::Clear(const Color& color)
	{
		SDL_SetRenderDrawColor(s_Renderer, color.R, color.G, color.B, color.A);
		SDL_RenderClear(s_Renderer);
	}
	void Renderer2D::EnableAntiAliasing(bool v)
	{
		s_AntiAliasing = v;
	}
	void Renderer2D::DisableAntiAlising()
	{
		s_AntiAliasing = false;
	}
	void Renderer2D::PutPixel(int x, int y, int r, int g, int b, int a)
	{
		pixelRGBA(s_Renderer, x, y, r, g, b, a);
	}
	void Renderer2D::PutPixel(int x, int y, const Color& color)
	{
		pixelRGBA(s_Renderer, x, y, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
	{
		if (s_AntiAliasing)
			aalineRGBA(s_Renderer, x1, y1, x2, y1, r, g, b, a);
		else
			lineRGBA(s_Renderer, x1, y1, x2, y1, r, g, b, a);
	}
	void Renderer2D::DrawLine(int x1, int y1, int x2, int y2, const Color& color)
	{
		if (s_AntiAliasing)
			aalineRGBA(s_Renderer, x1, y1, x2, y1, color.R, color.G, color.B, color.A);
		else
			lineRGBA(s_Renderer, x1, y1, x2, y1, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::DrawRect(int x, int y, int w, int h, int r, int g, int b, int a)
	{
		rectangleRGBA(s_Renderer, x, y, x + w, y + h, r, g, b, a);
	}
	void Renderer2D::DrawRect(int x, int y, int w, int h, const Color& color)
	{
		rectangleRGBA(s_Renderer, x, y, x + w, y + h, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::FillRect(int x, int y, int w, int h, int r, int g, int b, int a)
	{
		boxRGBA(s_Renderer, x, y, x + w, y + h, r, g, b, a);
	}
	void Renderer2D::FillRect(int x, int y, int w, int h, const Color& color)
	{
		boxRGBA(s_Renderer, x, y, x + w, y + h, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::DrawRoundedRect(int x, int y, int w, int h, int rad, int r, int g, int b, int a)
	{
		roundedRectangleRGBA(s_Renderer, x, y, x + w, y + h, rad, r, g, b, a);
	}
	void Renderer2D::DrawRoundedRect(int x, int y, int w, int h, int rad, const Color& color)
	{
		roundedRectangleRGBA(s_Renderer, x, y, x + w, y + h, rad, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::FillRoundedRect(int x, int y, int w, int h, int rad, int r, int g, int b, int a)
	{
		roundedBoxRGBA(s_Renderer, x, y, x + w, y + h, rad, r, g, b, a);
	}
	void Renderer2D::FillRoundedRect(int x, int y, int w, int h, int rad, const Color& color)
	{
		roundedBoxRGBA(s_Renderer, x, y, x + w, y + h, rad, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::DrawCircle(int x, int y, int rad, int r, int g, int b, int a)
	{
		if (s_AntiAliasing)
			aacircleRGBA(s_Renderer, x, y, rad, r, g, b, a);
		else
			circleRGBA(s_Renderer, x, y, rad, r, g, b, a);
	}
	void Renderer2D::DrawCircle(int x, int y, int rad, const Color& color)
	{
		if (s_AntiAliasing)
			aacircleRGBA(s_Renderer, x, y, rad, color.R, color.G, color.B, color.A);
		else
			circleRGBA(s_Renderer, x, y, rad, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::FillCircle(int x, int y, int rad, int r, int g, int b, int a)
	{
		filledCircleRGBA(s_Renderer, x, y, rad, r, g, b, a);
	}
	void Renderer2D::FillCircle(int x, int y, int rad, const Color& color)
	{
		filledCircleRGBA(s_Renderer, x, y, rad, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::DrawEllipse(int x, int y, int w, int h, int r, int g, int b, int a)
	{
		if (s_AntiAliasing)
			aaellipseRGBA(s_Renderer, x + w, y + h, w, h, r, g, b, a);
		else
			ellipseRGBA(s_Renderer, x + w, y + h, w, h, r, g, b, a);
	}
	void Renderer2D::DrawEllipse(int x, int y, int w, int h, const Color& color)
	{
		if (s_AntiAliasing)
			aaellipseRGBA(s_Renderer, x + w, y + h, w, h, color.R, color.G, color.B, color.A);
		else
			ellipseRGBA(s_Renderer, x + w, y + h, w, h, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::FillEllipse(int x, int y, int w, int h, int r, int g, int b, int a)
	{
		filledEllipseRGBA(s_Renderer, x + w, y + h, w, h, r, g, b, a);
	}
	void Renderer2D::FillEllipse(int x, int y, int w, int h, const Color& color)
	{
		filledEllipseRGBA(s_Renderer, x + w, y + h, w, h, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::DrawTrigon(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a)
	{
		if (s_AntiAliasing)
			aatrigonRGBA(s_Renderer, x1, y1, x2, y2, x3, y3, r, g, b, a);
		else
			trigonRGBA(s_Renderer, x1, y1, x2, y2, x3, y3, r, g, b, a);
	}
	void Renderer2D::DrawTrigon(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color)
	{
		if (s_AntiAliasing)
			aatrigonRGBA(s_Renderer, x1, y1, x2, y2, x3, y3, color.R, color.G, color.B, color.A);
		else
			trigonRGBA(s_Renderer, x1, y1, x2, y2, x3, y3, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::FillTrigon(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a)
	{
		filledTrigonRGBA(s_Renderer, x1, y1, x2, y2, x3, y3, r, g, b, a);
	}
	void Renderer2D::FillTrigon(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color)
	{
		filledTrigonRGBA(s_Renderer, x1, y1, x2, y2, x3, y3, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::DrawPolygon(Sint16* x, Sint16* y, int n, int r, int g, int b, int a)
	{
		if (s_AntiAliasing)
			aapolygonRGBA(s_Renderer, x, y, n, r, g, b, a);
		else
			polygonRGBA(s_Renderer, x, y, n, r, g, b, a);
	}
	void Renderer2D::DrawPolygon(Sint16* x, Sint16* y, int n, const Color& color)
	{
		if (s_AntiAliasing)
			aapolygonRGBA(s_Renderer, x, y, n, color.R, color.G, color.B, color.A);
		else
			polygonRGBA(s_Renderer, x, y, n, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::FillPolygon(Sint16* x, Sint16* y, int n, int r, int g, int b, int a)
	{
		filledPolygonRGBA(s_Renderer, x, y, n, r, g, b, a);
	}
	void Renderer2D::FillPolygon(Sint16* x, Sint16* y, int n, const Color& color)
	{
		filledPolygonRGBA(s_Renderer, x, y, n, color.R, color.G, color.B, color.A);
	}
	void Renderer2D::DrawRotatedRect(int x, int y, int w, int h, int angle, int r, int g, int b, int a)
	{
		SDL_Texture* texture = SDL_CreateTexture(s_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_Rect rect = { x, y, w, h };
		SDL_SetRenderTarget(s_Renderer, texture);
		DrawRect(0, 0, w, h, r, g, b, a);
		SDL_SetRenderTarget(s_Renderer, NULL);
		SDL_RenderCopyEx(s_Renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
		SDL_DestroyTexture(texture);
	}
	void Renderer2D::DrawRotatedRect(int x, int y, int w, int h, int angle, const Color& color)
	{
		SDL_Texture* texture = SDL_CreateTexture(s_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_Rect rect = { x, y, w, h };
		SDL_SetRenderTarget(s_Renderer, texture);
		DrawRect(0, 0, w, h, color);
		SDL_SetRenderTarget(s_Renderer, NULL);
		SDL_RenderCopyEx(s_Renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
		SDL_DestroyTexture(texture);
	}
	void Renderer2D::FillRotatedRect(int x, int y, int w, int h, int angle, int r, int g, int b, int a)
	{
		SDL_Texture* texture = SDL_CreateTexture(s_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_Rect rect = { x, y, w, h };
		SDL_SetRenderTarget(s_Renderer, texture);
		Clear(r, g, b, a);
		SDL_SetRenderTarget(s_Renderer, NULL);
		SDL_RenderCopyEx(s_Renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
		SDL_DestroyTexture(texture);
	}
	void Renderer2D::FillRotatedRect(int x, int y, int w, int h, int angle, const Color& color)
	{
		SDL_Texture* texture = SDL_CreateTexture(s_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_Rect rect = { x, y, w, h };
		SDL_SetRenderTarget(s_Renderer, texture);
		Clear(color);
		SDL_SetRenderTarget(s_Renderer, NULL);
		SDL_RenderCopyEx(s_Renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
		SDL_DestroyTexture(texture);
	}
	void Renderer2D::SetFont(const std::string& path, int size)
	{
		s_Font = TTF_OpenFont(path.c_str(), size);
	}
	void Renderer2D::SetFontStyle(int style)
	{
		TTF_SetFontStyle(s_Font, style);
	}
	void Renderer2D::SetFontOutline(int thickness)
	{
		TTF_SetFontOutline(s_Font, thickness);
	}
	void Renderer2D::SetFontHinting(int hinting)
	{
		TTF_SetFontHinting(s_Font, hinting);
	}
	void Renderer2D::SetFontKerning(bool value)
	{
		TTF_SetFontKerning(s_Font, value);
	}
	void Renderer2D::RenderText(const std::string& text, int x, int y, int r, int g, int b, int a)
	{
		SDL_Color color = { r, g, b, a };
		SDL_Surface* temp = TTF_RenderText_Solid(s_Font, text.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(s_Renderer, temp);
		SDL_Rect rect = { x, y, temp->w, temp->h };
		SDL_RenderCopy(s_Renderer, texture, NULL, &rect);
		SDL_FreeSurface(temp);
	}
	void Renderer2D::RenderText(const std::string& text, int x, int y, const Color& color)
	{
		SDL_Color col = { color.R, color.G, color.B, color.A };
		SDL_Surface* temp = TTF_RenderText_Solid(s_Font, text.c_str(), col);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(s_Renderer, temp);
		SDL_Rect rect = { x, y, temp->w, temp->h };
		SDL_RenderCopy(s_Renderer, texture, NULL, &rect);
		SDL_FreeSurface(temp);
	}
	void Renderer2D::RenderRotatedText(const std::string& text, int x, int y, int angle, int r, int g, int b, int a)
	{
		SDL_Color color = { r, g, b, a };
		SDL_Surface* temp = TTF_RenderText_Solid(s_Font, text.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(s_Renderer, temp);
		SDL_Rect rect = { x, y, temp->w, temp->h };
		SDL_RenderCopyEx(s_Renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
		SDL_FreeSurface(temp);
	}
	void Renderer2D::RenderRotatedText(const std::string& text, int x, int y, int angle, const Color& color)
	{
		SDL_Color col = { color.R, color.G, color.B, color.A };
		SDL_Surface* temp = TTF_RenderText_Solid(s_Font, text.c_str(), col);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(s_Renderer, temp);
		SDL_Rect rect = { x, y, temp->w, temp->h };
		SDL_RenderCopyEx(s_Renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
		SDL_FreeSurface(temp);
	}
	void Renderer2D::RenderTexture(SDL_Texture* texture, const Vector2& position, const Vector2& size, const Color& color)
	{
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureColorMod(texture, color.R, color.G, color.B);
		SDL_SetTextureAlphaMod(texture, color.A);
		SDL_RenderCopy(s_Renderer, texture, NULL, &Vector2::VecsToRect(position, size));
	}
	void Renderer2D::RenderRotatedTexture(SDL_Texture* texture, const Vector2& position, const Vector2& size, int angle, const Color& color)
	{
		SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureColorMod(texture, color.R, color.G, color.B);
		SDL_SetTextureAlphaMod(texture, color.A);
		SDL_RenderCopyEx(s_Renderer, texture, NULL, &Vector2::VecsToRect(position, size), angle, NULL, SDL_FLIP_NONE);
	}
}