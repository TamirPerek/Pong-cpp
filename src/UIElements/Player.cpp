#include "Player.h"

Player::Player(const WindowSize& xWindowSize, std::map<int, bool>& xKeysPressed, int xButtonUp, int xButtonDown)
	: UIBaseElement{ SDL_FRect{0, 0, static_cast<float>(xWindowSize.w / (30 * xWindowSize.wRatio)), static_cast<float>(xWindowSize.h / 4)} },
	mWindowSize{ xWindowSize },
	mKeysPressed{ xKeysPressed },
	mButtonUp{ xButtonUp },
	mButtonDown{ xButtonDown }
{
}

void Player::update(Player &xPlayer, const WindowSize& xWindowSize) noexcept
{
	if (xPlayer.mKeysPressed.get().at(xPlayer.mButtonUp) && xPlayer.mFRect.y > 0)
		xPlayer.mFRect.y -= static_cast<float>(5 * xPlayer.mWindowSize.hRatio);
	if (xPlayer.mKeysPressed.get().at(xPlayer.mButtonDown) && xPlayer.mFRect.y + xPlayer.mFRect.h < xPlayer.mWindowSize.h)
		xPlayer.mFRect.y += static_cast<float>(5 * xPlayer.mWindowSize.hRatio);

	if (xWindowSize == xPlayer.mWindowSize)
		return;

	xPlayer.mFRect.w = (xPlayer.mFRect.w * xWindowSize.w) / xPlayer.mWindowSize.w;
	xPlayer.mFRect.h = (xPlayer.mFRect.h * xWindowSize.h) / xPlayer.mWindowSize.h;
	xPlayer.mFRect.x = (xPlayer.mFRect.x * xWindowSize.w) / xPlayer.mWindowSize.w;
	xPlayer.mFRect.y = (xPlayer.mFRect.y * xWindowSize.h) / xPlayer.mWindowSize.h;

	xPlayer.mWindowSize = xWindowSize;
}

void Player::render(Player &xPlayer, SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_FRect*>(xPlayer));
}
