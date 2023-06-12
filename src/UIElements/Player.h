#pragma once

#include "UIElement.h"

#include <map>

class Player : public UIElement
{
public:
	WindowSize mWindowSize;
	std::map<int, bool>& mKeysPressed;
	int mButtonUp{ 0 };
	int mButtonDown{ 0 };

	explicit Player(const WindowSize& xWindowSize, std::map<int, bool>& xKeysPressed, int xButtonUp, int xButtonDown);

	~Player() final = default;

	Player& update(const WindowSize& xWindowSize) noexcept final;
	Player& render(SDL_Renderer&) noexcept final;
};
