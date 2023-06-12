#include "MiddleLine.h"

MiddleLine::MiddleLine(const WindowSize &xWindowSize)
    : UIElement{SDL_Rect{0,0, static_cast<int>((xWindowSize.w / 80) * xWindowSize.wRatio), xWindowSize.h}},
      mWindowSize{xWindowSize}
{
}

MiddleLine &MiddleLine::update(const WindowSize &xWindowSize) noexcept
{
	if (mWindowSize == xWindowSize)
		return *this;

	mRect.w = (mRect.w * xWindowSize.w) / mWindowSize.w;
	mRect.h = (mRect.h * xWindowSize.h) / mWindowSize.h;
	mRect.x = (mRect.x * xWindowSize.w) / mWindowSize.w;
	mRect.y = (mRect.y * xWindowSize.h) / mWindowSize.h;

	mWindowSize = xWindowSize;

    return *this;
}

MiddleLine &MiddleLine::render(SDL_Renderer &xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 80, 80, 80, 200);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_Rect*>(*this));

    return *this;
}
