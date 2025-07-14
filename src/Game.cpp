#include "Game.h"

#include "Configure.h"
#include "SDLElements.h"
#include "WindowSize.h"
#include "UIElements/Field.h"
#include "UIElements/UIFunctions.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>

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
	tMiddleLine.mFRect.x = (xWindowSize.w / 2) - (tMiddleLine.mFRect.w / 2);
	tResult.emplace_back(std::move(tMiddleLine));

	Player tPlayerOne{xWindowSize, xKeysPressed, SDLK_UP, SDLK_DOWN};
	tPlayerOne.mFRect.x = xWindowSize.w - (tPlayerOne.mFRect.w * 2);
	tPlayerOne.mFRect.y = (xWindowSize.h / 2) - (tPlayerOne.mFRect.h / 2);
	tResult.emplace_back(std::move(tPlayerOne));

	Player tPlayerTwo{xWindowSize, xKeysPressed, SDLK_W, SDLK_S};
	tPlayerTwo.mFRect.x = tPlayerTwo.mFRect.w;
	tPlayerTwo.mFRect.y = (xWindowSize.h / 2) - (tPlayerTwo.mFRect.h / 2);
	tResult.emplace_back(std::move(tPlayerTwo));

	Points tPoints{xWindowSize};
	tPoints.mFRect.x = (xWindowSize.w / 2) - (tPoints.mFRect.w / 2);
	tResult.emplace_back(std::move(tPoints));

	// Because std::variant copy
	Ball tBall{xWindowSize, std::get<Player>(tResult.at(2)), std::get<Player>(tResult.at(3)), std::get<Points>(tResult.at(4))};
	tResult.emplace_back(std::move(tBall));

	return tResult;
}

static inline void InitSDL() noexcept(false)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw std::runtime_error("Unable to init SDL");
	if (!TTF_Init())
		throw std::runtime_error("Unable to init SDL TTF");
}

int Game::Start() noexcept
{
	try
	{
		InitSDL();

		unique_window_t window{SDL_CreateWindow("Pong", 1028, 720, SDL_WINDOW_RESIZABLE)};
		unique_renderer_t tRenderer{SDL_CreateRenderer(window.get(), nullptr)};

		WindowSize tWindowSize{*window};

		std::map<int, bool> tKeyPressed{{SDLK_UP, false}, {SDLK_DOWN, false}, {SDLK_W, false}, {SDLK_S, false}, {SDLK_ESCAPE, false}};

		auto tUIElements{CreateElements(tWindowSize, tKeyPressed)};

		bool isQuit = false;
		SDL_Event event;

		while (!isQuit)
		{
			SDL_Delay(10);
			SDL_PollEvent(&event);

			switch (event.type)
			{
			case SDL_EVENT_QUIT:
				isQuit = true;
				break;
			case SDL_EVENT_KEY_DOWN:
				if (auto tRes = tKeyPressed.find(event.key.key); tRes != tKeyPressed.end())
					tRes->second = true;
				break;
			case SDL_EVENT_KEY_UP:
				if (auto tRes = tKeyPressed.find(event.key.key); tRes != tKeyPressed.end())
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
    
		SDL_Quit();
		return EXIT_FAILURE;
	}
}
