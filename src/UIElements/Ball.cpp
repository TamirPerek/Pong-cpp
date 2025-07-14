#include "Ball.h"

#include <random>
#include <functional>

Ball::Ball(const WindowSize &xWindowSize, const std::reference_wrapper<Player> xPlayerOne, const std::reference_wrapper<Player> xPlayerTwo, std::reference_wrapper<Points> xPoints)
	: UIBaseElement{SDL_FRect{0, 0, static_cast<float>(xWindowSize.h / (30 * xWindowSize.hRatio)), static_cast<float>(xWindowSize.h / (30 * xWindowSize.hRatio))}},
	  mWindowSize{xWindowSize},
	  mPlayerOne{xPlayerOne},
	  mPlayerTwo{xPlayerTwo},
	  mPoints{xPoints}
{
	Reset();
}

void Ball::update(Ball &xBall, const WindowSize& xWindowSize) noexcept
{
	if (xBall.mXSpeed > 0 && SDL_HasRectIntersectionFloat(static_cast<const SDL_FRect*>(xBall), static_cast<const SDL_FRect*>(xBall.mPlayerOne.get())))
		xBall.mXSpeed *= -1.0;

	if (xBall.mXSpeed < 0 && SDL_HasRectIntersectionFloat(static_cast<const SDL_FRect*>(xBall), static_cast<const SDL_FRect*>(xBall.mPlayerTwo.get())))
		xBall.mXSpeed *= -1.0;

	if (xBall.mFRect.y < 0 || xBall.mFRect.y + xBall.mFRect.h > xBall.mWindowSize.h)
		xBall.mYSpeed *= -1.0;

	xBall.mFRect.x += static_cast<float>(xBall.mXSpeed * xWindowSize.wRatio);
	xBall.mFRect.y += static_cast<float>(xBall.mYSpeed * xBall.mWindowSize.hRatio);
	xBall.mXSpeed *= xBall.mForce;
	xBall.mYSpeed *= xBall.mForce;

	// Points
	if (xBall.mFRect.x + xBall.mFRect.w < 0)
	{
		xBall.Reset();
		++xBall.mPoints.get().mValueTwo;
		// if (mPoints->mValueTwo == 9)
		// 	run = false;
	}

	if (xBall.mFRect.x > xBall.mWindowSize.w)
	{
		xBall.Reset();
		++xBall.mPoints.get().mValueOne;
		// if (mPoints->mValueOne == 9)
		// 	run = false;
	}

	if (xWindowSize == xBall.mWindowSize)
		return ;

	xBall.mFRect.w = (xBall.mFRect.h * xWindowSize.h) / xBall.mWindowSize.h;
	xBall.mFRect.h = (xBall.mFRect.h * xWindowSize.h) / xBall.mWindowSize.h;
	xBall.mFRect.x = (xBall.mFRect.x * xWindowSize.w) / xBall.mWindowSize.w;
	xBall.mFRect.y = (xBall.mFRect.y * xWindowSize.h) / xBall.mWindowSize.h;
	xBall.mXSpeed = (xBall.mXSpeed * xWindowSize.w) / xBall.mWindowSize.w;
	xBall.mYSpeed = (xBall.mYSpeed * xWindowSize.h) / xBall.mWindowSize.h;

	xBall.mWindowSize = xWindowSize;
}

void Ball::render(Ball &xBall, SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_FRect*>(xBall));
}

void Ball::Reset() noexcept
{
	static auto tGen{ std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine()) };

	mFRect.x = mWindowSize.w / 2;
	mFRect.y = mWindowSize.h / 2;

	mXSpeed = (mXSpeed < 0.0 ? 5.0 : -5.0) / mWindowSize.wRatio;
	mYSpeed = (tGen() != 0 ? -2.0 : 2.0) / mWindowSize.hRatio;
}
