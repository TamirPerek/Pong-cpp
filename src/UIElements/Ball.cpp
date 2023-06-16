#include "Ball.h"

#include <random>
#include <functional>
#include <cassert>

Ball::Ball(const WindowSize& xWindowSize, const std::shared_ptr<UIElement>& xPlayerOne, const std::shared_ptr<UIElement>& xPlayerTwo, std::shared_ptr<Points> xPoints)
	: UIElement{ SDL_Rect{0, 0, static_cast<int>(xWindowSize.h / (30 * xWindowSize.hRatio)), static_cast<int>(xWindowSize.h / (30 * xWindowSize.hRatio))} },
	mWindowSize{ xWindowSize },
	mPlayerOne{ xPlayerOne },
	mPlayerTwo{ xPlayerTwo },
	mPoints{ xPoints }
{
	Resett();
}

Ball& Ball::update(const WindowSize& xWindowSize) noexcept
{
	if (mXSpeed > 0 && SDL_HasIntersection(static_cast<const SDL_Rect*>(*this), static_cast<const SDL_Rect*>(*mPlayerOne)) == SDL_TRUE)
		mXSpeed *= -1.0;

	if (mXSpeed < 0 && SDL_HasIntersection(static_cast<const SDL_Rect*>(*this), static_cast<const SDL_Rect*>(*mPlayerTwo)) == SDL_TRUE)
		mXSpeed *= -1.0;

	if (mRect.y < 0 || mRect.y + mRect.h > mWindowSize.h)
		mYSpeed *= -1.0;

	mRect.x += static_cast<int>(mXSpeed * xWindowSize.wRatio);
	mRect.y += static_cast<int>(mYSpeed * mWindowSize.hRatio);
	mXSpeed *= mForce;
	mYSpeed *= mForce;

	// Points
	if (mRect.x + mRect.w < 0)
	{
		Resett();
		++mPoints->mValueTwo;
		// if (mPoints->mValueTwo == 9)
		// 	run = false;
	}

	if (mRect.x > mWindowSize.w)
	{
		Resett();
		++mPoints->mValueOne;
		// if (mPoints->mValueOne == 9)
		// 	run = false;
	}

	if (xWindowSize == mWindowSize)
		return *this;

	mRect.w = (mRect.h * xWindowSize.h) / mWindowSize.h;
	mRect.h = (mRect.h * xWindowSize.h) / mWindowSize.h;
	mRect.x = (mRect.x * xWindowSize.w) / mWindowSize.w;
	mRect.y = (mRect.y * xWindowSize.h) / mWindowSize.h;
	mXSpeed = (mXSpeed * xWindowSize.w) / mWindowSize.w;
	mYSpeed = (mYSpeed * xWindowSize.h) / mWindowSize.h;

	mWindowSize = xWindowSize;

	return *this;
}

Ball& Ball::render(SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(&xRenderer, static_cast<const SDL_Rect*>(*this));

	return *this;
}

void Ball::Resett() noexcept
{
	static auto tGen{ std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine()) };

	mRect.x = mWindowSize.w / 2;
	mRect.y = mWindowSize.h / 2;
	mXSpeed = (mXSpeed < 0.0 ? 5.0 : -5.0) * mWindowSize.wRatio;
	mYSpeed = (tGen() != 0 ? -2.0 : 2.0) * mWindowSize.hRatio;
}
