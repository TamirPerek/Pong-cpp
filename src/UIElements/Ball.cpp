#include "Ball.h"

#include <random>
#include <functional>
#include <cassert>

Ball::Ball(const WindowSize& xWindowSize, const Player& xPlayerOne, const Player& xPlayerTwo, Points& xPoints)
	: UIBaseElement{ SDL_Rect{0, 0, static_cast<int>(xWindowSize.h / (30 * xWindowSize.hRatio)), static_cast<int>(xWindowSize.h / (30 * xWindowSize.hRatio))} },
	mWindowSize{ xWindowSize },
	mPlayerOne{ xPlayerOne },
	mPlayerTwo{ xPlayerTwo },
	mPoints{ xPoints }
{
	Resett();
}

void Ball::update(Ball &xBall, const WindowSize& xWindowSize) noexcept
{
	if (xBall.mXSpeed > 0 && SDL_HasIntersection(static_cast<const SDL_Rect*>(xBall), static_cast<const SDL_Rect*>(xBall.mPlayerOne)) == SDL_TRUE)
		xBall.mXSpeed *= -1.0;

	if (xBall.mXSpeed < 0 && SDL_HasIntersection(static_cast<const SDL_Rect*>(xBall), static_cast<const SDL_Rect*>(xBall.mPlayerTwo)) == SDL_TRUE)
		xBall.mXSpeed *= -1.0;

	if (xBall.mRect.y < 0 || xBall.mRect.y + xBall.mRect.h > xBall.mWindowSize.h)
		xBall.mYSpeed *= -1.0;

	xBall.mRect.x += static_cast<int>(xBall.mXSpeed * xWindowSize.wRatio);
	xBall.mRect.y += static_cast<int>(xBall.mYSpeed * xBall.mWindowSize.hRatio);
	xBall.mXSpeed *= xBall.mForce;
	xBall.mYSpeed *= xBall.mForce;

	// Points
	if (xBall.mRect.x + xBall.mRect.w < 0)
	{
		xBall.Resett();
		++xBall.mPoints.mValueTwo;
		// if (mPoints->mValueTwo == 9)
		// 	run = false;
	}

	if (xBall.mRect.x > xBall.mWindowSize.w)
	{
		xBall.Resett();
		++xBall.mPoints.mValueOne;
		// if (mPoints->mValueOne == 9)
		// 	run = false;
	}

	if (xWindowSize == xBall.mWindowSize)
		return ;

	xBall.mRect.w = (xBall.mRect.h * xWindowSize.h) / xBall.mWindowSize.h;
	xBall.mRect.h = (xBall.mRect.h * xWindowSize.h) / xBall.mWindowSize.h;
	xBall.mRect.x = (xBall.mRect.x * xWindowSize.w) / xBall.mWindowSize.w;
	xBall.mRect.y = (xBall.mRect.y * xWindowSize.h) / xBall.mWindowSize.h;
	xBall.mXSpeed = (xBall.mXSpeed * xWindowSize.w) / xBall.mWindowSize.w;
	xBall.mYSpeed = (xBall.mYSpeed * xWindowSize.h) / xBall.mWindowSize.h;

	xBall.mWindowSize = xWindowSize;
}

void Ball::render(Ball &xBall, SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_Rect*>(xBall));
}

void Ball::Resett() noexcept
{
	static auto tGen{ std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine()) };

	mRect.x = mWindowSize.w / 2;
	mRect.y = mWindowSize.h / 2;
	mXSpeed = (mXSpeed < 0.0 ? 5.0 : -5.0) * mWindowSize.wRatio;
	mYSpeed = (tGen() != 0 ? -2.0 : 2.0) * mWindowSize.hRatio;
}
