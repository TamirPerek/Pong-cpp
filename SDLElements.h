#pragma once
#include <SDL_video.h>
#include <SDL_surface.h>
#include <SDL_render.h>
#include <memory>

struct SDLWindowDeleter
{
    void operator()(SDL_Window *xWindow)
    {
        if (xWindow)
            SDL_DestroyWindow(xWindow);
    }
};
struct SDLSurfaceDeleter
{
    void operator()(SDL_Surface *xSurface)
    {
        if (xSurface)
            SDL_FreeSurface(xSurface);
    }
};

struct SDLRendererDeleter
{
    void operator()(SDL_Renderer *xRenderer)
    {
        if (xRenderer)
            SDL_DestroyRenderer(xRenderer);
    }
};

using unique_window_t = std::unique_ptr<SDL_Window, SDLWindowDeleter>;
using unique_surface_t = std::unique_ptr<SDL_Surface, SDLSurfaceDeleter>;
using unique_renderer_t = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>;