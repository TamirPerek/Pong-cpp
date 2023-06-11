#pragma once

#include "SDLElements.h"
#include <SDL_rect.h>

class WindowSize
{
public:
    int w{0};
    int h{0};
    double wRatio{1.0};
    double hRatio{1.0};

    WindowSize() = default;
    explicit WindowSize(const unique_window_t &xWindow)
    {
        SDL_GL_GetDrawableSize(xWindow.get(), &w, &h);
        int tW{0};
        int tH{0};
        SDL_GetWindowSize(xWindow.get(), &tW, &tH);
        wRatio = static_cast<double>(w) / tW;
        hRatio = static_cast<double>(h) / tH;
    }

    bool operator==(const WindowSize &xOther)
    {
        return w == xOther.w && h == xOther.h;
    }
    bool operator!=(const WindowSize &xOther)
    {
        return !(*this == xOther);
    }
    SDL_Rect GetRect() const noexcept
    {
        return SDL_Rect{0, 0, w, h};
    }
};
