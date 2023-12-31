#pragma once

#include "Font.h"
#include "Text.h"
#include "Model.h"
#include "ParticleSystem.h"
#include "Texture.h"

#include <string>
#include "SDL2-2.28.1/include/SDL.h"

namespace neu
{
	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();

		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame();
		void EndFrame();

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawPoint(int x, int y);
		void DrawPoint(float x, float y);
		void DrawTexture(class Texture* texture, const Transform& transform, bool horizontalFlip = false, bool verticalFlip = false);
		void DrawTexture(class Texture* texture, const Rect& source, const Transform& transform, bool horizontalFlip = false, bool verticalFlip = false);
		void DrawTexture(class Texture* texture, const Rect& source, const Transform& transform, bool horizontalFlip, const vec2& origin);

		int GetWidth() const { return m_width; };
		int GetHeight() const { return m_height; };

		friend class Text;
		friend class Texture;

	private:
		int m_width;
		int m_height;

		void DrawHitBox(class CollisionComponent* collision, Color color = { 1, 0, 0, 1 });

		SDL_Renderer* m_renderer = nullptr;
		SDL_Window* m_window = nullptr;
	};

	extern Renderer g_renderer;
}