#include "Ball.h"

#include <random>
#include <functional>
#include <cassert>

Ball::Ball(const WindowSize& xWindowSize, const Player &xPlayerOne, const Player &xPlayerTwo)
	: UIElement{ SDL_Rect{0, 0, static_cast<int>((xWindowSize.h / 50) * xWindowSize.hRatio), static_cast<int>((xWindowSize.h / 50) * xWindowSize.hRatio)} },
	mWindowSize{ xWindowSize },
	mPlayerOne{xPlayerOne},
	mPlayerTwo{xPlayerTwo}
{
	Resett();
}

void Ball::update(const WindowSize& xWindowSize) noexcept
{
	if (mXSpeed > 0 && SDL_HasIntersection(static_cast<const SDL_Rect*>(*this), static_cast<const SDL_Rect*>(mPlayerOne)) == SDL_TRUE)
		mXSpeed *= -1.0;

	if (mXSpeed < 0 && SDL_HasIntersection(static_cast<const SDL_Rect*>(*this), static_cast<const SDL_Rect*>(mPlayerTwo)) == SDL_TRUE)
		mXSpeed *= -1.0;

	if (mRect.y < 0 || mRect.y + mRect.h > mWindowSize.h)
		mYSpeed *= -1.0;

	mRect.x += static_cast<int>(mXSpeed * xWindowSize.wRatio);
	mRect.y += static_cast<int>(mYSpeed * mWindowSize.hRatio);
	mXSpeed *= mForce;
	mYSpeed *= mForce;

	if (xWindowSize == mWindowSize)
		return;

	mRect.w = (mRect.h * xWindowSize.h) / mWindowSize.h;
	mRect.h = (mRect.h * xWindowSize.h) / mWindowSize.h;
	mRect.x = (mRect.x * xWindowSize.w) / mWindowSize.w;
	mRect.y = (mRect.y * xWindowSize.h) / mWindowSize.h;

	mWindowSize = xWindowSize;
}

void Ball::render(SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_Rect*>(*this));
}

void Ball::Resett() noexcept
{
	static auto tGen{ std::bind_front(std::uniform_int_distribution<>(0, 1), std::default_random_engine()) };

	mRect.x = mWindowSize.w / 2;
	mRect.y = mWindowSize.h / 2;
	mXSpeed = mXSpeed < 0.0 ? 2.0 : -2.0;
	mYSpeed = tGen() != 0 ? -1.0 : 1.0;
}
