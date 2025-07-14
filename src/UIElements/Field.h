#pragma once

#include "UIBaseElement.h"
#include "../WindowSize.h"

class Field final : public UIBaseElement
{
public:
	Field();
	Field(const Field&) = default;
	Field(Field&&) = default;

	static void update(Field &, const WindowSize& xWindowSize) noexcept;
	static void render(Field &, SDL_Renderer&) noexcept;
};