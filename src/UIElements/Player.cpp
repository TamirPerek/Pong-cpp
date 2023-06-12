#include "Player.h"

Player::Player(const WindowSize& xWindowSize)
	: UIElement{ SDL_Rect{0, 0, xWindowSize.w / 50, xWindowSize.h / 4} },
	mWindowSize{ xWindowSize }
{
}

void Player::update(const WindowSize& xWindowSize) noexcept
{
	if (xWindowSize == mWindowSize)
		return;

	mRect.w = (mRect.w * xWindowSize.w) / mWindowSize.w;
	mRect.h = (mRect.h * xWindowSize.h) / mWindowSize.h;
	mRect.x = (mRect.x * xWindowSize.w) / mWindowSize.w;
	mRect.y = (mRect.y * xWindowSize.h) / mWindowSize.h;

	mWindowSize = xWindowSize;
}

void Player::render(SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_Rect*>(*this));
}

