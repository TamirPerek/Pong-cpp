#include "Field.h"

Field::Field()
	: UIBaseElement{ SDL_Rect{} }
{
}

void Field::update(Field &, [[maybe_unused]] const WindowSize& xWindowSize) noexcept
{
	return;
}

void Field::render(Field &, SDL_Renderer& xRenderer) noexcept
{
	SDL_SetRenderDrawColor(&xRenderer, 66, 66, 66, 255);
	SDL_RenderClear(&xRenderer);
}
