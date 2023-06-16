#pragma once

#include "../WindowSize.h"

#include <SDL_rect.h>
#include <SDL_render.h>

class UIBaseElement
{
public:
	SDL_Rect mRect;

	explicit UIBaseElement(const SDL_Rect& xRect);
	explicit UIBaseElement(SDL_Rect&& xRect);

	virtual ~UIBaseElement() = default;
	// virtual UIBaseElement &update(const WindowSize& xWindowSize) noexcept = 0;
	// virtual UIBaseElement &render(SDL_Renderer&) noexcept = 0;
	explicit operator SDL_Rect const* () const;
	explicit operator SDL_Rect* ();
};
