#pragma once

#include "Field.h"
#include "Player.h"
#include "MiddleLine.h"
#include "Points.h"
#include "Ball.h"

#include <variant>

class Ball;

class WindowSize;
class SDL_Renderer;

using UIElement = std::variant<Ball, Field, Player, MiddleLine, Points>;

namespace UIFunctions
{
    void Update(UIElement &, const WindowSize &) noexcept(false);
    void Render(UIElement &, SDL_Renderer &) noexcept(false);
}