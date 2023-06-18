#include "Game.h"

#include "Configure.h"
#include "SDLElements.h"
#include "WindowSize.h"
#include "UIElements/Field.h"
#include "UIElements/UIFunctions.h"

#include <SDL_ttf.h>
#include <SDL.h>

#ifdef SUPPORT_STD_FORMAT_LIB
#include <format>
#else
#include <fmt/format.h>
#endif

#include <iostream>
#include <algorithm>
#include <stdexcept>

#ifdef TEST_THING
std::cout << "Hello";
#endif

static inline std::vector<UIElement> CreateElements(const WindowSize &xWindowSize, std::map<int, bool> &xKeysPressed) noexcept(false)
{
	std::vector<UIElement> tResult;

	Field tField;
	tResult.emplace_back(std::move(tField));

	MiddleLine tMiddleLine{xWindowSize};
	tMiddleLine.mRect.x = (xWindowSize.w / 2) - (tMiddleLine.mRect.w / 2);
	tResult.emplace_back(std::move(tMiddleLine));

	Player tPlayerOne{xWindowSize, xKeysPressed, SDLK_UP, SDLK_DOWN};
	tPlayerOne.mRect.x = xWindowSize.w - (tPlayerOne.mRect.w * 2);
	tPlayerOne.mRect.y = (xWindowSize.h / 2) - (tPlayerOne.mRect.h / 2);
	tResult.emplace_back(std::move(tPlayerOne));

	Player tPlayerTwo{xWindowSize, xKeysPressed, SDLK_w, SDLK_s};
	tPlayerTwo.mRect.x = tPlayerTwo.mRect.w;
	tPlayerTwo.mRect.y = (xWindowSize.h / 2) - (tPlayerTwo.mRect.h / 2);
	tResult.emplace_back(std::move(tPlayerTwo));

	Points tPoints{xWindowSize};
	tPoints.mRect.x = (xWindowSize.w / 2) - (tPoints.mRect.w / 2);
	tResult.emplace_back(std::move(tPoints));

	// Because std::variant copys
	Ball tBall{xWindowSize, std::get<Player>(tResult.at(2)), std::get<Player>(tResult.at(3)), std::get<Points>(tResult.at(4))};
	tResult.emplace_back(std::move(tBall));

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

			for (auto &tUIElement : tUIElements)
			{
				UIFunctions::Update(tUIElement, tWindowSize);
				UIFunctions::Render(tUIElement, *tRenderer);
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
#ifdef SUPPORT_STD_FORMAT_LIB
		std::cerr << std::format("Fatal Error: {}\n", e.what());
#else
		std::cerr << fmt::format("Fatal Error: {}\n", e.what());
#endif
		return EXIT_FAILURE;
	}
}
