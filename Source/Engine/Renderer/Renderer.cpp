#include "Renderer.h"
#include "Texture.h"
#include "SDL2-2.28.1/include/SDL_ttf.h"
#include "SDL2-2.28.1/include/SDL_image.h"

namespace neu
{

	bool Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();

		return true;
	}

	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		IMG_Quit();
		TTF_Quit();
	}

	void Renderer::CreateWindow(const std::string& title, int width, int height)
	{
		m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

		m_height = height;
		m_width = width;
	}

	void Renderer::BeginFrame()
	{
		SDL_RenderClear(m_renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	}

	void Renderer::DrawLine(int x1, int y1, int x2, int y2)
	{
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawPoint(int x, int y)
	{
		SDL_RenderDrawPoint(m_renderer, x, y);
	}

	void Renderer::DrawPoint(float x, float y)
	{
		SDL_RenderDrawPointF(m_renderer, x, y);
	}

	void Renderer::DrawTexture(Texture* texture, const Transform& transform, bool horizontalFlip, bool verticalFlip) 
	{
		mat3 mx = transform.GetMatrix();

		vec2 size = texture->GetSize() * mx.GetScale();
		vec2 position = mx.GetTranslation();
		float angle = -RadiansToDegrees(mx.GetRotation());

		SDL_Rect dest;
		dest.x = (int)(position.x - (size.x * 0.5f));
		dest.y = (int)(position.y - (size.y * 0.5f));
		dest.w = (int)size.x;
		dest.h = (int)size.y;
		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx

		if (horizontalFlip) SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, (double)angle, nullptr, SDL_FLIP_HORIZONTAL);
		else if (verticalFlip) SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, (double)angle, nullptr, SDL_FLIP_VERTICAL);
		else SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, (double)angle, nullptr, SDL_FLIP_NONE);
	}

	void Renderer::DrawTexture(Texture* texture, const Rect& source, const Transform& transform, bool horizontalFlip, bool verticalFlip)
	{
		mat3 mx = transform.GetMatrix();

		vec2 size = vec2{source.w, source.h} * mx.GetScale();
		vec2 position = mx.GetTranslation();
		float angle = -RadiansToDegrees(mx.GetRotation());

		SDL_Rect dest;
		dest.x = (int)(position.x - (size.x * 0.5f));
		dest.y = (int)(position.y - (size.y * 0.5f));
		dest.w = (int)size.x;
		dest.h = (int)size.y;
		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx

		if (horizontalFlip) SDL_RenderCopyEx(m_renderer, texture->m_texture, (SDL_Rect*)&source, &dest, (double)angle, nullptr, SDL_FLIP_HORIZONTAL);
		else if (verticalFlip) SDL_RenderCopyEx(m_renderer, texture->m_texture, (SDL_Rect*)&source, &dest, (double)angle, nullptr, SDL_FLIP_VERTICAL);
		else SDL_RenderCopyEx(m_renderer, texture->m_texture, (SDL_Rect*)&source, &dest, (double)angle, nullptr, SDL_FLIP_NONE);
	}

	void Renderer::DrawTexture(Texture* texture, const Rect& source, const Transform& transform, bool horizontalFlip, const vec2& origin)
	{
		mat3 mx = transform.GetMatrix();

		vec2 size = vec2{ source.w, source.h } *mx.GetScale();
		vec2 position = mx.GetTranslation();
		float angle = -RadiansToDegrees(mx.GetRotation());

		SDL_Rect dest;
		dest.x = (int)(position.x - (size.x * origin.x));
		dest.y = (int)(position.y - (size.y * origin.y));
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_Point center{(int)(size.x * origin.x), (int)(size.y * origin.y) };

		// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
		SDL_RenderCopyEx(m_renderer, texture->m_texture, (SDL_Rect*)&source, &dest, (double)angle, &center, 
			horizontalFlip ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}

	Renderer g_renderer;
}
