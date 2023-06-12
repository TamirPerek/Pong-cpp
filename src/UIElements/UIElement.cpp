#include "UIElement.h"

UIElement::UIElement(const SDL_Rect& xRect)
	: mRect{ xRect }
{
}

UIElement::UIElement(SDL_Rect&& xRect)
	: mRect{ std::move(xRect) }
{
}

UIElement::operator SDL_Rect const* () const
{
	return &mRect;
}

UIElement::operator SDL_Rect* ()
{
	return &mRect;
}
