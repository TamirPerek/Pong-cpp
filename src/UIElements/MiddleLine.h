#pragma once

#include "UIElement.h"

class MiddleLine : public UIElement
{
public:
    WindowSize mWindowSize;

    explicit MiddleLine(const WindowSize &xWindowSize);
    ~MiddleLine() final = default;

    MiddleLine &update(const WindowSize &xWindowSize) noexcept final;
    MiddleLine &render(SDL_Renderer &xRenderer) noexcept final;
};