#include "SDLElements.h"
#include "WindowSize.h"

#include <SDL_ttf.h>
#include <SDL.h>

#include <map>
#include <iostream>
#include <random>

class UIElement
{
public:
	SDL_Rect mRect;

	explicit UIElement(const SDL_Rect &xRect) : mRect{xRect} {}
	explicit UIElement(SDL_Rect &&xRect) : mRect{std::move(xRect)} {}

	~UIElement() = default;
	virtual void update(const WindowSize &xWindowSize) noexcept = 0;
	operator SDL_Rect const *() const
	{
		return &mRect;
	}
	operator SDL_Rect *()
	{
		return &mRect;
	}
};

class Player : public UIElement
{
public:
	WindowSize mWindowSize;

	explicit Player(const WindowSize &xWindowSize) : mWindowSize{xWindowSize}, UIElement{SDL_Rect{0, 0, xWindowSize.w / 40, xWindowSize.h / 4}}
	{
	}

	~Player() = default;

	void update(const WindowSize &xWindowSize) noexcept final
	{
		if (xWindowSize == mWindowSize)
			return;

		mRect.w = (mRect.w * xWindowSize.w) / mWindowSize.w;
		mRect.h = (mRect.h * xWindowSize.h) / mWindowSize.h;
		mRect.x = (mRect.x * xWindowSize.w) / mWindowSize.w;
		mRect.y = (mRect.y * xWindowSize.h) / mWindowSize.h;

		mWindowSize = xWindowSize;
	}
};

class Ball : public UIElement
{
public:
	WindowSize mWindowSize;
	double mXSpeed{2.0};
	double mYSpeed{1.0};
	constexpr static double mForce = 1.0005;

	explicit Ball(const WindowSize &xWindowSize)
		: mWindowSize{xWindowSize},
		  UIElement{SDL_Rect{0, 0, static_cast<int>((xWindowSize.h / 50) * xWindowSize.hRatio), static_cast<int>((xWindowSize.h / 50) * xWindowSize.hRatio)}}
	{
		Resett();
	}
	~Ball() = default;

	void update(const WindowSize &xWindowSize) noexcept final
	{
		assert(false);
	}

	void update(const WindowSize &xWindowSize, const Player &xPlayerOne, const Player &xPlayerTwo) noexcept
	{
		if (mXSpeed > 0 && SDL_HasIntersection(*this, xPlayerOne) == SDL_TRUE)
			mXSpeed *= -1.0;

		if (mXSpeed < 0 && SDL_HasIntersection(*this, xPlayerTwo) == SDL_TRUE)
			mXSpeed *= -1.0;

		if (mRect.y < 0 || mRect.y + mRect.h > mWindowSize.h)
			mYSpeed *= -1.0;

		mRect.x += static_cast<int>(mXSpeed * xWindowSize.wRatio);
		mRect.y += static_cast<int>(mYSpeed * mWindowSize.hRatio);
		mXSpeed *= mForce;
		mYSpeed *= mForce;

		if (xWindowSize == mWindowSize)
			return;

		mRect.w = (mRect.h * xWindowSize.h) / mWindowSize.h;
		mRect.h = (mRect.h * xWindowSize.h) / mWindowSize.h;
		mRect.x = (mRect.x * xWindowSize.w) / mWindowSize.w;
		mRect.y = (mRect.y * xWindowSize.h) / mWindowSize.h;

		mWindowSize = xWindowSize;
	}

	void Resett() noexcept
	{
		static auto tGen{std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine())};

		mRect.x = mWindowSize.w / 2;
		mRect.y = mWindowSize.h / 2;
		mXSpeed = mXSpeed < 0.0 ? 2.0 : -2.0;
		mYSpeed = tGen() != 0 ? -1.0 : 1.0;
	}
};

class Points : public UIElement
{
public:
	WindowSize mWindowSize;
	// TTF_Font *Sans{TTF_OpenFont("Sans.ttf", 24)};
	// SDL_Color White{255, 255, 255};
	unsigned int mValue{0U};
	// unique_surface_t mMessage;

	explicit Points(const WindowSize &xWindowSize)
		: mWindowSize{xWindowSize},
		  UIElement{SDL_Rect{0, 0, 100, 100}}
	{
	}

	~Points() = default;

	void update(const WindowSize &xWindowSize) noexcept final
	{
		assert(false);
	}

	void update(const WindowSize &xWindowSize, unique_renderer_t &xRenderer) noexcept
	{
		auto tFont = TTF_OpenFont("img/DS-DIGI.TTF", 24);
		if (!tFont)
		{
			std::cerr << "Konnte Font nicht laden\n";
			return;
		}

		unique_surface_t tMessageSurface{TTF_RenderText_Solid(tFont, "99", SDL_Color{255, 255, 255})};
		if (!tMessageSurface)
		{
			std::cerr << "Konnte tMessageSurface nicht rendern\n";
			return;
		}

		SDL_Texture *Message = SDL_CreateTextureFromSurface(xRenderer.get(), tMessageSurface.get());
		if (!Message)
		{
			std::cerr << "Konnte Message nicht erstellen\n";
			return;
		}

		SDL_RenderCopy(xRenderer.get(), Message, NULL, *this);
		SDL_DestroyTexture(Message);
		TTF_CloseFont(tFont);
	}
};

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return EXIT_FAILURE;
	if (TTF_Init() != 0)
		return EXIT_FAILURE;

	unique_window_t window{SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1028, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)};
	unique_renderer_t tRenderer{SDL_CreateRenderer(window.get(), -1, 0U)};
	int x = 580;
	int y = 160;

	WindowSize tWindowSize{window};

	Player tPlayerOne{tWindowSize};
	tPlayerOne.mRect.x = tWindowSize.w - (tPlayerOne.mRect.w * 2);
	tPlayerOne.mRect.y = (tWindowSize.h / 2) - (tPlayerOne.mRect.h / 2);

	Player tPlayerTwo{tWindowSize};
	tPlayerTwo.mRect.x = tPlayerTwo.mRect.w;
	tPlayerTwo.mRect.y = (tWindowSize.h / 2) - (tPlayerTwo.mRect.h / 2);

	Ball tBall{tWindowSize};

	Points tPointsPlayerOne{tWindowSize};

	bool isquit = false;
	SDL_Event event;

	std::map<int, bool> tKeyPressed{{SDLK_UP, false}, {SDLK_DOWN, false}, {SDLK_w, false}, {SDLK_s, false}, {SDLK_ESCAPE, false}};
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

		if (tKeyPressed.at(SDLK_UP))
			tPlayerOne.mRect.y -= (5 * tWindowSize.hRatio);
		if (tKeyPressed.at(SDLK_DOWN))
			tPlayerOne.mRect.y += (5 * tWindowSize.hRatio);
		if (tKeyPressed.at(SDLK_w))
			tPlayerTwo.mRect.y -= (5 * tWindowSize.hRatio);
		if (tKeyPressed.at(SDLK_s))
			tPlayerTwo.mRect.y += (5 * tWindowSize.hRatio);
		if (tKeyPressed.at(SDLK_ESCAPE))
		{
			isquit = true;
			break;
		}

		tWindowSize = WindowSize{window};
		tPlayerOne.update(tWindowSize);
		tPlayerTwo.update(tWindowSize);
		tBall.update(tWindowSize, tPlayerOne, tPlayerTwo);
		tPointsPlayerOne.update(tWindowSize, tRenderer);

		SDL_SetRenderDrawColor(tRenderer.get(), 66, 66, 66, 255);
		SDL_RenderClear(tRenderer.get());
		tPointsPlayerOne.update(tWindowSize, tRenderer);

		SDL_SetRenderDrawColor(tRenderer.get(), 255, 255, 255, 255);
		SDL_RenderFillRect(tRenderer.get(), tBall);

		SDL_SetRenderDrawColor(tRenderer.get(), 255, 255, 255, 255);
		SDL_RenderFillRect(tRenderer.get(), tPlayerOne);

		SDL_SetRenderDrawColor(tRenderer.get(), 255, 255, 255, 255);
		SDL_RenderFillRect(tRenderer.get(), tPlayerTwo);

		SDL_RenderPresent(tRenderer.get());

		// Points
		if (tBall.mRect.x + tBall.mRect.w < 0)
			tBall.Resett();

		if (tBall.mRect.x > tWindowSize.w)
			tBall.Resett();
	}

	SDL_Quit();
}
