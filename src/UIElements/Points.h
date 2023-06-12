#pragma once

#include "UIElement.h"
#include "../SDLElements.h"
#include <SDL_ttf.h>

class Points : public UIElement
{
public:
	WindowSize mWindowSize;
	unique_font_t mFont{ TTF_OpenFont("assets/The Led Display St.ttf", 72) };
	unsigned int mValueOne{ 0U };
	unsigned int mValueTwo{ 0U };

	explicit Points(const WindowSize& xWindowSize);

	~Points() final = default;

	Points& update(const WindowSize& xWindowSize) noexcept final;
	Points& render(SDL_Renderer&) noexcept final;
};
