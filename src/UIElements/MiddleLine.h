#pragma once

#include "UIBaseElement.h"
#include "../WindowSize.h"

class MiddleLine final : public UIBaseElement
{
public:
    WindowSize mWindowSize;

    explicit MiddleLine(const WindowSize &xWindowSize);

    static void update(MiddleLine &, const WindowSize &xWindowSize) noexcept;
    static void render(MiddleLine &, SDL_Renderer &xRenderer) noexcept;
};