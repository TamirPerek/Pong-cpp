#pragma once

#include "UIBaseElement.h"
#include "Points.h"
#include "Player.h"

class Ball : public UIBaseElement
{
public:
	WindowSize mWindowSize;
	double mXSpeed{ 2.0 };
	double mYSpeed{ 1.0 };
	constexpr static double mForce = 1.0005;
	const std::reference_wrapper<Player> mPlayerOne;
	const std::reference_wrapper<Player> mPlayerTwo;
	std::reference_wrapper<Points> mPoints;

	Ball(const Ball&) = default;
	Ball(Ball&&) = default;

	explicit Ball(const WindowSize &xWindowSize, const std::reference_wrapper<Player> xPlayerOne, const std::reference_wrapper<Player> xPlayerTwo, std::reference_wrapper<Points> xPoints);
	~Ball() final = default;

	static void update(Ball &, const WindowSize& xWindowSize) noexcept;
	static void render(Ball &, SDL_Renderer&) noexcept;

	void Resett() noexcept;
};