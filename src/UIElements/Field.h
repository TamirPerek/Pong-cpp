#pragma once

#include "UIBaseElement.h"

class Field : public UIBaseElement
{
public:
	Field();
	Field(const Field&) = default;
	Field(Field&&) = default;
	~Field() final = default;

	static void update(Field &, const WindowSize& xWindowSize) noexcept;
	static void render(Field &, SDL_Renderer&) noexcept;
};