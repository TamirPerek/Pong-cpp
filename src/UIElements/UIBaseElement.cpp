#include "UIBaseElement.h"

UIBaseElement::UIBaseElement(const SDL_Rect& xRect)
	: mRect{ xRect }
{
}

UIBaseElement::UIBaseElement(SDL_Rect&& xRect)
	: mRect{ std::move(xRect) }
{
}

UIBaseElement::operator SDL_Rect const* () const
{
	return &mRect;
}

UIBaseElement::operator SDL_Rect* ()
{
	return &mRect;
}
