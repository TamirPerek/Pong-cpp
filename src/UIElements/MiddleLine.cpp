#include "MiddleLine.h"

MiddleLine::MiddleLine(const WindowSize &xWindowSize)
    : UIBaseElement{SDL_FRect{0,0, static_cast<float>(xWindowSize.w / (80 * xWindowSize.wRatio)), static_cast<float>(xWindowSize.h)}},
      mWindowSize{xWindowSize}
{
}

void MiddleLine::update(MiddleLine &xMiddleLine, const WindowSize &xWindowSize) noexcept
{
	if (xMiddleLine.mWindowSize == xWindowSize)
		return ;

	xMiddleLine.mFRect.w = (xMiddleLine.mFRect.w * xWindowSize.w) / xMiddleLine.mWindowSize.w;
	xMiddleLine.mFRect.h = (xMiddleLine.mFRect.h * xWindowSize.h) / xMiddleLine.mWindowSize.h;
	xMiddleLine.mFRect.x = (xMiddleLine.mFRect.x * xWindowSize.w) / xMiddleLine.mWindowSize.w;
	xMiddleLine.mFRect.y = (xMiddleLine.mFRect.y * xWindowSize.h) / xMiddleLine.mWindowSize.h;

	xMiddleLine.mWindowSize = xWindowSize;
}

void MiddleLine::render(MiddleLine &xMiddleLine, SDL_Renderer &xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 80, 80, 80, 200);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_FRect*>(xMiddleLine));
}
