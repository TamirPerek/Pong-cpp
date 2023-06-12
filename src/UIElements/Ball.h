#pragma once

#include "UIElement.h"
#include "Points.h"

class Ball : public UIElement
{
public:
	WindowSize mWindowSize;
	double mXSpeed{ 2.0 };
	double mYSpeed{ 1.0 };
	constexpr static double mForce = 1.0005;
	const std::shared_ptr<UIElement> mPlayerOne;
	const std::shared_ptr<UIElement> mPlayerTwo;
	std::shared_ptr<Points> mPoints;

	explicit Ball(const WindowSize& xWindowSize, const std::shared_ptr<UIElement>& xPlayerOne, const std::shared_ptr<UIElement>& xPlayerTwo, std::shared_ptr<Points> xPoints);
	~Ball() final = default;

	Ball& update(const WindowSize& xWindowSize) noexcept final;
	Ball& render(SDL_Renderer&) noexcept final;

	void Resett() noexcept;
};