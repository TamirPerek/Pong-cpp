#include "Player.h"

Player::Player(const WindowSize& xWindowSize, std::map<int, bool>& xKeysPressed, int xButtonUp, int xButtonDown)
	: UIBaseElement{ SDL_Rect{0, 0, static_cast<int>(xWindowSize.w / (30 * xWindowSize.wRatio)), static_cast<int>(xWindowSize.h / 4)} },
	mWindowSize{ xWindowSize },
	mKeysPressed{ xKeysPressed },
	mButtonUp{ xButtonUp },
	mButtonDown{ xButtonDown }
{
}

void Player::update(Player &xPlayer, const WindowSize& xWindowSize) noexcept
{
	if (xPlayer.mKeysPressed.get().at(xPlayer.mButtonUp) && xPlayer.mRect.y > 0)
		xPlayer.mRect.y -= static_cast<int>(5 * xPlayer.mWindowSize.hRatio);
	if (xPlayer.mKeysPressed.get().at(xPlayer.mButtonDown) && xPlayer.mRect.y + xPlayer.mRect.h < xPlayer.mWindowSize.h)
		xPlayer.mRect.y += static_cast<int>(5 * xPlayer.mWindowSize.hRatio);

	if (xWindowSize == xPlayer.mWindowSize)
		return;

	xPlayer.mRect.w = (xPlayer.mRect.w * xWindowSize.w) / xPlayer.mWindowSize.w;
	xPlayer.mRect.h = (xPlayer.mRect.h * xWindowSize.h) / xPlayer.mWindowSize.h;
	xPlayer.mRect.x = (xPlayer.mRect.x * xWindowSize.w) / xPlayer.mWindowSize.w;
	xPlayer.mRect.y = (xPlayer.mRect.y * xWindowSize.h) / xPlayer.mWindowSize.h;

	xPlayer.mWindowSize = xWindowSize;
}

void Player::render(Player &xPlayer, SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_Rect*>(xPlayer));
}
