#include "Game.h"

#include "SDLElements.h"
#include "WindowSize.h"
#include "UIElements/Player.h"
#include "UIElements/Points.h"
#include "UIElements/Ball.h"
#include "UIElements/Field.h"
#include "UIElements/MiddleLine.h"

#include <SDL_ttf.h>
#include <SDL.h>

#include <fmt/format.h>

#include <algorithm>
#include <stdexcept>

static inline std::vector<std::shared_ptr<UIElement>> CreateElements(const WindowSize &xWindowSize, std::map<int, bool> &xKeysPressed) noexcept(false)
{
	std::vector<std::shared_ptr<UIElement>> tResult;

	std::shared_ptr<UIElement> tField{std::make_shared<Field>()};

	std::shared_ptr<UIElement> tMiddleLine{std::make_shared<MiddleLine>(xWindowSize)};
	tMiddleLine->mRect.x = (xWindowSize.w / 2) - (tMiddleLine->mRect.w / 2);

	std::shared_ptr<UIElement> tPlayerOne{std::make_shared<Player>(xWindowSize, xKeysPressed, SDLK_UP, SDLK_DOWN)};
	tPlayerOne->mRect.x = xWindowSize.w - (tPlayerOne->mRect.w * 2);
	tPlayerOne->mRect.y = (xWindowSize.h / 2) - (tPlayerOne->mRect.h / 2);

	std::shared_ptr<UIElement> tPlayerTwo{std::make_shared<Player>(xWindowSize, xKeysPressed, SDLK_w, SDLK_s)};
	tPlayerTwo->mRect.x = tPlayerTwo->mRect.w;
	tPlayerTwo->mRect.y = (xWindowSize.h / 2) - (tPlayerTwo->mRect.h / 2);

	std::shared_ptr<UIElement> tPoints{std::make_shared<Points>(xWindowSize)};
	tPoints->mRect.x = (xWindowSize.w / 2) - (tPoints->mRect.w / 2);

	std::shared_ptr<UIElement> tBall{std::make_shared<Ball>(xWindowSize, tPlayerOne, tPlayerTwo, std::static_pointer_cast<Points>(tPoints))};

	tResult.emplace_back(std::move(tField));
	tResult.emplace_back(std::move(tMiddleLine));
	tResult.emplace_back(std::move(tPlayerOne));
	tResult.emplace_back(std::move(tPlayerTwo));
	tResult.emplace_back(std::move(tBall));
	tResult.emplace_back(std::move(tPoints));

	return tResult;
}

static inline void InitSDL() noexcept(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error("Unable to init SDL");
	if (TTF_Init() != 0)
		throw std::runtime_error("Unable to init SDL TTF");
}

int Game::Start() noexcept
{
	try
	{
		InitSDL();

		unique_window_t window{SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1028, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)};
		unique_renderer_t tRenderer{SDL_CreateRenderer(window.get(), -1, 0U)};

		WindowSize tWindowSize{*window};

		std::map<int, bool> tKeyPressed{{SDLK_UP, false}, {SDLK_DOWN, false}, {SDLK_w, false}, {SDLK_s, false}, {SDLK_ESCAPE, false}};

		auto tUIElements{CreateElements(tWindowSize, tKeyPressed)};

		bool isquit = false;
		SDL_Event event;

		bool run{true};

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

			if (tKeyPressed.at(SDLK_ESCAPE))
			{
				tUIElements.clear();
				tUIElements = CreateElements(tWindowSize, tKeyPressed);
			}

			tWindowSize = WindowSize{*window};

			SDL_SetRenderDrawColor(tRenderer.get(), 66, 66, 66, 255);
			SDL_RenderClear(tRenderer.get());

			for (auto &tUIElement : tUIElements)
			{
				tUIElement->update(tWindowSize)
					.render(*tRenderer);
			}

			SDL_RenderPresent(tRenderer.get());

			if (!run)
				continue;
		}

		SDL_Quit();

		return EXIT_SUCCESS;
	}
	catch (const std::exception &e)
	{
		fmt::print("Fatal Error: {}\n", e.what());
		return EXIT_FAILURE;
	}
}
