#include "Field.h"

Field::Field()
	: UIElement{ SDL_Rect{} }
{
}

Field& Field::update(const WindowSize& xWindowSize) noexcept
{
	return *this;
}

Field& Field::render(SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 66, 66, 66, 255);
	SDL_RenderClear(&xRenderer);

	return *this;
}
