#pragma once

#include "UIElement.h"

class Field : public UIElement
{
public:
	Field();
	~Field() final = default;

	Field& update(const WindowSize& xWindowSize) noexcept final;
	Field& render(SDL_Renderer&) noexcept final;
};