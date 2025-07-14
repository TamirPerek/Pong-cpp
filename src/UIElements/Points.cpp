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

Points::Points(const WindowSize& xWindowSize)
	: UIBaseElement{ SDL_FRect{0, 0, static_cast<float>(250 * xWindowSize.wRatio), static_cast<float>(100 * xWindowSize.hRatio)} },
	mWindowSize{ xWindowSize }
{
	const auto tFontPath{mFontPath};
	if (std::error_code er; !std::filesystem::exists(tFontPath, er))
            throw std::runtime_error(std::format("file does not exist: {}, {}", tFontPath.string(), er.message()));

	mFont.reset(TTF_OpenFont(tFontPath.string().c_str(), mFontSize));

	if (!mFont)
		throw std::runtime_error(std::format("Unable to load font: {}", tFontPath.string()));
}

Points::Points(const Points &xOther)
: UIBaseElement{ xOther.mFRect },
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

	xPoints.mFRect.w = (xPoints.mFRect.w * xWindowSize.w) / xPoints.mWindowSize.w;
	xPoints.mFRect.h = (xPoints.mFRect.h * xWindowSize.h) / xPoints.mWindowSize.h;
	xPoints.mFRect.x = (xPoints.mFRect.x * xWindowSize.w) / xPoints.mWindowSize.w;
	xPoints.mFRect.y = (xPoints.mFRect.y * xWindowSize.h) / xPoints.mWindowSize.h;

	xPoints.mWindowSize = xWindowSize;
}

void Points::render(Points &xPoints, SDL_Renderer& xRenderer) noexcept
{
#ifdef SUPPORT_STD_FORMAT_LIB
	auto tScore = std::format("{} : {}", xPoints.mValueOne, xPoints.mValueTwo);
#else
	auto tScore = fmt::format("{} : {}", xPoints.mValueOne, xPoints.mValueTwo);
#endif

	unique_surface_t tMessageSurface{ TTF_RenderText_Solid(xPoints.mFont.get(), tScore.c_str(), tScore.size(), SDL_Color{255, 255, 255}) };
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


	if (!SDL_RenderTexture(&xRenderer, Message.get(), nullptr, static_cast<const SDL_FRect*>(xPoints)))
		std::cerr << "Unable to show points\n";
}

