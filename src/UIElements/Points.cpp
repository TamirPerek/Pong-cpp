#include "Points.h"

#include <fmt/format.h>

#include <cassert>
#include <iostream>

Points::Points(const WindowSize& xWindowSize)
	: UIElement{ SDL_Rect{0, 0, static_cast<int>(250 * xWindowSize.wRatio), static_cast<int>(100 * xWindowSize.hRatio)} },
	mWindowSize{ xWindowSize }
{
	if (!mFont)
	{
		constexpr static std::string_view errormsg{ "Error: unable to load font\n" };
		std::cerr << errormsg;
		throw std::runtime_error(errormsg.data());
	}
}

void Points::update(const WindowSize& xWindowSize) noexcept
{
	assert(false);
}

void Points::update(const WindowSize& xWindowSize, SDL_Renderer& xRenderer) noexcept
{
	auto tScore = fmt::format("{} : {}", mValueOne, mValueTwo);
	unique_surface_t tMessageSurface{ TTF_RenderText_Solid(mFont.get(), tScore.c_str(), SDL_Color{255, 255, 255}) };
	if (!tMessageSurface)
	{
		std::cerr << "Unable to render text\n";
	}

	unique_texture_t Message{ SDL_CreateTextureFromSurface(&xRenderer, tMessageSurface.get()) };
	if (!Message)
	{
		std::cerr << "Unable to create texture\n";
		return;
	}

	if (SDL_RenderCopy(&xRenderer, Message.get(), nullptr, static_cast<const SDL_Rect*>(*this)) != 0)
		std::cerr << "Unable to show points\n";

	if (mWindowSize == xWindowSize)
		return;

	mRect.w = (mRect.w * xWindowSize.w) / mWindowSize.w;
	mRect.h = (mRect.h * xWindowSize.h) / mWindowSize.h;
	mRect.x = (mRect.x * xWindowSize.w) / mWindowSize.w;
	mRect.y = (mRect.y * xWindowSize.h) / mWindowSize.h;

	mWindowSize = xWindowSize;
}
