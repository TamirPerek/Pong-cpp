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
    explicit WindowSize(SDL_Window &xWindow)
    {
        SDL_GL_GetDrawableSize(&xWindow, &w, &h);
        int tW{0};
        int tH{0};
        SDL_GetWindowSize(&xWindow, &tW, &tH);
        wRatio = static_cast<double>(w) / tW;
        hRatio = static_cast<double>(h) / tH;
    }

    bool operator==(const WindowSize &xOther) const
    {
        return w == xOther.w && h == xOther.h;
    }
};
