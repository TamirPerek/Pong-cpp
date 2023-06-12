#pragma once

#include "UIElement.h"
#include "Player.h"

class Ball : public UIElement
{
public:
	WindowSize mWindowSize;
	double mXSpeed{ 2.0 };
	double mYSpeed{ 1.0 };
	constexpr static double mForce = 1.0005;

	explicit Ball(const WindowSize& xWindowSize);
	~Ball() final = default;

	[[noreturn]] void update(const WindowSize& xWindowSize) noexcept final;

	void update(const WindowSize& xWindowSize, const Player& xPlayerOne, const Player& xPlayerTwo) noexcept;

	void Resett() noexcept;
};