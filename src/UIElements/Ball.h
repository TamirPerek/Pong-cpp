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
	const Player &mPlayerOne;
	const Player &mPlayerTwo;

	explicit Ball(const WindowSize& xWindowSize, const Player &xPlayerOne, const Player &xPlayerTwo);
	~Ball() final = default;

	void update(const WindowSize& xWindowSize) noexcept final;
	void render(SDL_Renderer&) noexcept final;

	void Resett() noexcept;
};