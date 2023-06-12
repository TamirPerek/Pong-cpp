#pragma once

#include "../WindowSize.h"

#include <SDL_rect.h>

class UIElement
{
public:
	SDL_Rect mRect;

	explicit UIElement(const SDL_Rect& xRect);
	explicit UIElement(SDL_Rect&& xRect);

	virtual ~UIElement() = default;
	virtual void update(const WindowSize& xWindowSize) noexcept = 0;
	explicit operator SDL_Rect const* () const;
	explicit operator SDL_Rect* ();
};
