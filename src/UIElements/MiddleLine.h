#pragma once

#include "UIBaseElement.h"

class MiddleLine : public UIBaseElement
{
public:
    WindowSize mWindowSize;

    explicit MiddleLine(const WindowSize &xWindowSize);
    ~MiddleLine() final = default;

    static void update(MiddleLine &, const WindowSize &xWindowSize) noexcept;
    static void render(MiddleLine &, SDL_Renderer &xRenderer) noexcept;
};