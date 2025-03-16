#include "UIBaseElement.h"

// UIBaseElement::UIBaseElement(const SDL_Rect& xRect)
// 	: mRect{ xRect }, mFRect{ .x = static_cast<float>(xRect.x), .y = static_cast<float>(xRect.y), .w = static_cast<float>(xRect.w), .h = static_cast<float>(xRect.h) }
// {
// }

// UIBaseElement::UIBaseElement(SDL_Rect&& xRect)
// 	: mRect{ std::move(xRect) }, mFRect{ .x = static_cast<float>(mRect.x), .y = static_cast<float>(mRect.y), .w = static_cast<float>(mRect.w), .h = static_cast<float>(mRect.h) }
// {
// }

UIBaseElement::UIBaseElement(const SDL_FRect& xRect)
	: mFRect{ xRect }
{
}

UIBaseElement::UIBaseElement(SDL_FRect&& xRect)
	: mFRect{ std::move(xRect) }
{
}

// UIBaseElement::operator SDL_Rect const* () const
// {
// 	return &mRect;
// }

// UIBaseElement::operator SDL_Rect* ()
// {
// 	return &mRect;
// }

UIBaseElement::operator SDL_FRect const *() const
{
	return &mFRect;
}

UIBaseElement::operator SDL_FRect* ()
{
	return &mFRect;
}
