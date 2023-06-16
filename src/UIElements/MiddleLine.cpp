#include "MiddleLine.h"

MiddleLine::MiddleLine(const WindowSize &xWindowSize)
    : UIBaseElement{SDL_Rect{0,0, static_cast<int>(xWindowSize.w / (80 * xWindowSize.wRatio)), xWindowSize.h}},
      mWindowSize{xWindowSize}
{
}

void MiddleLine::update(MiddleLine &xMiddleLine, const WindowSize &xWindowSize) noexcept
{
	if (xMiddleLine.mWindowSize == xWindowSize)
		return ;

	xMiddleLine.mRect.w = (xMiddleLine.mRect.w * xWindowSize.w) / xMiddleLine.mWindowSize.w;
	xMiddleLine.mRect.h = (xMiddleLine.mRect.h * xWindowSize.h) / xMiddleLine.mWindowSize.h;
	xMiddleLine.mRect.x = (xMiddleLine.mRect.x * xWindowSize.w) / xMiddleLine.mWindowSize.w;
	xMiddleLine.mRect.y = (xMiddleLine.mRect.y * xWindowSize.h) / xMiddleLine.mWindowSize.h;

	xMiddleLine.mWindowSize = xWindowSize;
}

void MiddleLine::render(MiddleLine &xMiddleLine, SDL_Renderer &xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 80, 80, 80, 200);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_Rect*>(xMiddleLine));
}
