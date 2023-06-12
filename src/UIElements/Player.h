#pragma once

#include "UIElement.h"

class Player : public UIElement
{
public:
	WindowSize mWindowSize;

	explicit Player(const WindowSize& xWindowSize);

	~Player() final = default;

	void update(const WindowSize& xWindowSize) noexcept final;
};