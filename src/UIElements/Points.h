#pragma once

#include "UIElement.h"
#include "../SDLElements.h"
#include <SDL_ttf.h>

class Points : public UIElement
{
public:
	WindowSize mWindowSize;
	unique_font_t mFont{ TTF_OpenFont("assets/DS-DIGI.TTF", 24) };
	unsigned int mValueOne{ 0U };
	unsigned int mValueTwo{ 0U };

	explicit Points(const WindowSize& xWindowSize);

	~Points() final = default;

	[[noreturn]] void update(const WindowSize& xWindowSize) noexcept final;

	void update(const WindowSize& xWindowSize, SDL_Renderer& xRenderer) noexcept;
};
