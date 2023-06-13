#include "Player.h"

Player::Player(const WindowSize& xWindowSize, std::map<int, bool>& xKeysPressed, int xButtonUp, int xButtonDown)
	: UIElement{ SDL_Rect{0, 0, static_cast<int>(xWindowSize.w / (30 * xWindowSize.wRatio)), static_cast<int>(xWindowSize.h / 4)} },
	mWindowSize{ xWindowSize },
	mKeysPressed{ xKeysPressed },
	mButtonUp{ xButtonUp },
	mButtonDown{ xButtonDown }
{
}

Player& Player::update(const WindowSize& xWindowSize) noexcept
{
	if (mKeysPressed.at(mButtonUp) && mRect.y > 0)
		mRect.y -= static_cast<int>(5 * mWindowSize.hRatio);
	if (mKeysPressed.at(mButtonDown) && mRect.y + mRect.h < mWindowSize.h)
		mRect.y += static_cast<int>(5 * mWindowSize.hRatio);

	if (xWindowSize == mWindowSize)
		return *this;

	mRect.w = (mRect.w * xWindowSize.w) / mWindowSize.w;
	mRect.h = (mRect.h * xWindowSize.h) / mWindowSize.h;
	mRect.x = (mRect.x * xWindowSize.w) / mWindowSize.w;
	mRect.y = (mRect.y * xWindowSize.h) / mWindowSize.h;

	mWindowSize = xWindowSize;

	return *this;
}

Player& Player::render(SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_Rect*>(*this));

	return *this;
}
