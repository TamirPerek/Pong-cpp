#pragma once

#include <SDL3/SDL_rect.h>

class UIBaseElement
{
public:
	// SDL_Rect mRect;
	SDL_FRect mFRect;

	// explicit UIBaseElement(const SDL_Rect& xRect);
	// explicit UIBaseElement(SDL_Rect&& xRect);
	explicit UIBaseElement(const SDL_FRect& xRect);
	explicit UIBaseElement(SDL_FRect&& xRect);

	virtual ~UIBaseElement() = default;
	// explicit operator SDL_Rect const* () const;
	// explicit operator SDL_Rect* ();
	explicit operator SDL_FRect const* () const;
	explicit operator SDL_FRect* ();
};
