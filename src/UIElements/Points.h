#pragma once

#include "UIBaseElement.h"
#include "../SDLElements.h"
#include <SDL3_ttf/SDL_ttf.h>

#include <filesystem>

class Points : public UIBaseElement
{
public:
	WindowSize mWindowSize;
	unique_font_t mFont;
	unsigned int mValueOne{ 0U };
	unsigned int mValueTwo{ 0U };
 #if defined(__APPLE__)
	const std::filesystem::path mFontPath{"../Resources/assets/The Led Display St.ttf"};
#else
	const std::filesystem::path mFontPath{std::filesystem::current_path() / "assets/The Led Display St.ttf"};
#endif
	int mFontSize{72};

	explicit Points(const WindowSize& xWindowSize);
	Points(const Points &);

	~Points() final = default;

	static void update(Points &, const WindowSize& xWindowSize) noexcept;
	static void render(Points &, SDL_Renderer&) noexcept;
};
