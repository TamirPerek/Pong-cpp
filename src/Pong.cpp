#include "SDLElements.h"
#include "WindowSize.h"
#include "UIElements/Player.h"
#include "UIElements/Points.h"
#include "UIElements/Ball.h"

#include <SDL_ttf.h>
#include <SDL.h>

#include <map>
#include <vector>
#include <algorithm>

std::vector<UIElement> CreateElements(const WindowSize &xWindowSize) noexcept
{
	std::vector<UIElement> tResult;

	Player tPlayerOne{ xWindowSize };
	tPlayerOne.mRect.x = xWindowSize.w - (tPlayerOne.mRect.w * 2);
	tPlayerOne.mRect.y = (xWindowSize.h / 2) - (tPlayerOne.mRect.h / 2);
	tResult.emplace_back(tPlayerOne);

	Player tPlayerTwo{ xWindowSize };
	tPlayerTwo.mRect.x = tPlayerTwo.mRect.w;
	tPlayerTwo.mRect.y = (xWindowSize.h / 2) - (tPlayerTwo.mRect.h / 2);

	Ball tBall{ xWindowSize, tPlayerOne, tPlayerTwo };

	Points tPoints{ xWindowSize };
	tPoints.mRect.x = (xWindowSize.w / 2) - (tPoints.mRect.w / 2);

	return tResult;
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return EXIT_FAILURE;
	if (TTF_Init() != 0)
		return EXIT_FAILURE;

	unique_window_t window{ SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1028, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI) };
	unique_renderer_t tRenderer{ SDL_CreateRenderer(window.get(), -1, 0U) };

	WindowSize tWindowSize{ *window };

	auto tUIElements{CreateElements(tWindowSize)};

	bool isquit = false;
	SDL_Event event;

	bool run{ true };

	std::map<int, bool> tKeyPressed{ {SDLK_UP, false}, {SDLK_DOWN, false}, {SDLK_w, false}, {SDLK_s, false}, {SDLK_ESCAPE, false} };
	while (!isquit)
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			isquit = true;
			break;
		case SDL_KEYDOWN:
			if (auto tRes = tKeyPressed.find(event.key.keysym.sym); tRes != tKeyPressed.end())
				tRes->second = true;
			break;
		case SDL_KEYUP:
			if (auto tRes = tKeyPressed.find(event.key.keysym.sym); tRes != tKeyPressed.end())
				tRes->second = false;
			break;
		default:
			break;
		}

		// if (tKeyPressed.at(SDLK_UP) && tPlayerOne.mRect.y > 0)
		// 	tPlayerOne.mRect.y -= static_cast<int>(5 * tWindowSize.hRatio);
		// if (tKeyPressed.at(SDLK_DOWN) && tPlayerOne.mRect.y + tPlayerOne.mRect.h < tWindowSize.h)
		// 	tPlayerOne.mRect.y += static_cast<int>(5 * tWindowSize.hRatio);
		// if (tKeyPressed.at(SDLK_w) && tPlayerTwo.mRect.y > 0)
		// 	tPlayerTwo.mRect.y -= static_cast<int>(5 * tWindowSize.hRatio);
		// if (tKeyPressed.at(SDLK_s) && tPlayerTwo.mRect.y + tPlayerTwo.mRect.h < tWindowSize.h)
		// 	tPlayerTwo.mRect.y += static_cast<int>(5 * tWindowSize.hRatio);
		if (tKeyPressed.at(SDLK_ESCAPE))
			isquit = true;

		tWindowSize = WindowSize{ *window };

		SDL_SetRenderDrawColor(tRenderer.get(), 66, 66, 66, 255);
		SDL_RenderClear(tRenderer.get());

		std::ranges::for_each(tUIElements, [&tWindowSize, &tRenderer] (auto &xUIElement)
		{
			xUIElement.update(tWindowSize);
			xUIElement.render(*tRenderer);
		});

		// tPlayerOne.update(tWindowSize);
		// tPlayerTwo.update(tWindowSize);
		// tBall.update(tWindowSize);
		// tPoints.update(tWindowSize);
		// tBall.render(*tRenderer);
		// tPlayerOne.render(*tRenderer);
		// tPlayerTwo.render(*tRenderer);
		// tPoints.render(*tRenderer);

		SDL_RenderPresent(tRenderer.get());

		if (!run)
			continue;

		// Points
		// if (tBall.mRect.x + tBall.mRect.w < 0)
		// {
		// 	tBall.Resett();
		// 	++tPoints.mValueTwo;
		// 	if (tPoints.mValueTwo == 9)
		// 		run = false;
		// }

		// if (tBall.mRect.x > tWindowSize.w)
		// {
		// 	tBall.Resett();
		// 	++tPoints.mValueOne;
		// 	if (tPoints.mValueOne == 9)
		// 		run = false;
		// }
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}
