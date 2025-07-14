#pragma once

#include "UIBaseElement.h"
#include "../WindowSize.h"

#include <map>
#include <functional>

class Player final : public UIBaseElement
{
public:
	WindowSize mWindowSize;
	std::reference_wrapper<std::map<int, bool>> mKeysPressed;
	int mButtonUp{ 0 };
	int mButtonDown{ 0 };

	explicit Player(const WindowSize& xWindowSize, std::map<int, bool>& xKeysPressed, int xButtonUp, int xButtonDown);

	static void update(Player &, const WindowSize& xWindowSize) noexcept;
	static void render(Player &, SDL_Renderer&) noexcept;
};
