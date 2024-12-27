#include "Points.h"

#include "Configure.h"

#ifdef SUPPORT_STD_FORMAT_LIB
#include <format>
#else
#include <fmt/format.h>
#endif

#include <cassert>
#include <iostream>
#include <filesystem>
#include <print>

Points::Points(const WindowSize& xWindowSize)
	: UIBaseElement{ SDL_Rect{0, 0, static_cast<int>(250 * xWindowSize.wRatio), static_cast<int>(100 * xWindowSize.hRatio)} },
	mWindowSize{ xWindowSize }
{
	const auto tFontPath{mFontPath};
	std::print("Font Path: {}\n", tFontPath.string());
	if (std::error_code er; !std::filesystem::exists(tFontPath, er))
            throw std::runtime_error(std::format("file does not exist: {}, {}", tFontPath.string(), er.message()));
	// if(!std::filesystem::exists(tFontPath))
	// 	throw std::runtime_error(std::format("Font not found: {}", tFontPath.string()));

	mFont.reset(TTF_OpenFont(tFontPath.string().c_str(), mFontSize));

	if (!mFont)
		throw std::runtime_error(std::format("Unable to load font: {}", tFontPath.string()));
}

Points::Points(const Points &xOther)
: UIBaseElement{ xOther.mRect },
	mWindowSize{ xOther.mWindowSize }
{
	mFont.reset(TTF_OpenFont(xOther.mFontPath.string().c_str(), xOther.mFontSize));

	if (!mFont)
		throw std::runtime_error(std::format("Unable to load font: {}", xOther.mFontPath.string()));
}

void Points::update(Points &xPoints, const WindowSize& xWindowSize) noexcept
{
	if (xPoints.mWindowSize == xWindowSize)
		return;

	xPoints.mRect.w = (xPoints.mRect.w * xWindowSize.w) / xPoints.mWindowSize.w;
	xPoints.mRect.h = (xPoints.mRect.h * xWindowSize.h) / xPoints.mWindowSize.h;
	xPoints.mRect.x = (xPoints.mRect.x * xWindowSize.w) / xPoints.mWindowSize.w;
	xPoints.mRect.y = (xPoints.mRect.y * xWindowSize.h) / xPoints.mWindowSize.h;

	xPoints.mWindowSize = xWindowSize;
}

void Points::render(Points &xPoints, SDL_Renderer& xRenderer) noexcept
{
#ifdef SUPPORT_STD_FORMAT_LIB
	auto tScore = std::format("{} : {}", xPoints.mValueOne, xPoints.mValueTwo);
#else
	auto tScore = fmt::format("{} : {}", xPoints.mValueOne, xPoints.mValueTwo);
#endif

	unique_surface_t tMessageSurface{ TTF_RenderText_Solid(xPoints.mFont.get(), tScore.c_str(), SDL_Color{255, 255, 255}) };
	if (!tMessageSurface)
	{
		std::cerr << "Unable to render text\n";
	}

	unique_texture_t Message{ SDL_CreateTextureFromSurface(&xRenderer, tMessageSurface.get()) };
	if (!Message)
	{
		std::cerr << "Unable to create texture\n";
		return ;
	}

	if (SDL_RenderCopy(&xRenderer, Message.get(), nullptr, static_cast<const SDL_Rect*>(xPoints)) != 0)
		std::cerr << "Unable to show points\n";
}

