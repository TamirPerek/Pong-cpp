#pragma once

#include "UIBaseElement.h"
#include "../SDLElements.h"
#include <SDL_ttf.h>

#include <string_view>

class Points : public UIBaseElement
{
public:
	WindowSize mWindowSize;
	unique_font_t mFont;
	unsigned int mValueOne{ 0U };
	unsigned int mValueTwo{ 0U };
	std::string_view mFontPath{"assets/The Led Display St.ttf"};
	int mFontSize{72};

	explicit Points(const WindowSize& xWindowSize);
	Points(const Points &);

	~Points() final = default;

	static void update(Points &, const WindowSize& xWindowSize) noexcept;
	static void render(Points &, SDL_Renderer&) noexcept;
};
