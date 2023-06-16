#include "UIFunctions.h"

template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };

namespace UIFunctions
{
    void Update(UIElement &xUIElement, const WindowSize &xWindowSize) noexcept(false)
    {
        std::visit(overloaded{[&xWindowSize](Field &xField)
                              {
                                  Field::update(xField, xWindowSize);
                              },
                              [&xWindowSize](Player &xPlayer)
                              {
                                  Player::update(xPlayer, xWindowSize);
                              },
                              [&xWindowSize](MiddleLine &xMiddleLine)
                              {
                                  MiddleLine::update(xMiddleLine, xWindowSize);
                              },
                              [&xWindowSize](Points &xPoints)
                              {
                                  Points::update(xPoints, xWindowSize);
                              },
                              [&xWindowSize](Ball &xBall)
                              {
                                  Ball::update(xBall, xWindowSize);
                              }},
                   xUIElement);
    }
    void Render(UIElement &xUIElement, SDL_Renderer &xRenderer) noexcept(false)
    {
        std::visit(overloaded{[&xRenderer](Field &xField)
                              {
                                  Field::render(xField, xRenderer);
                              },
                              [&xRenderer](Player &xPlayer)
                              {
                                  Player::render(xPlayer, xRenderer);
                              },
                              [&xRenderer](MiddleLine &xMiddleLine)
                              {
                                  MiddleLine::render(xMiddleLine, xRenderer);
                              },
                              [&xRenderer](Points &xPoints)
                              {
                                  Points::render(xPoints, xRenderer);
                              },
                              [&xRenderer](Ball &xBall)
                              {
                                  Ball::render(xBall, xRenderer);
                              }},
                   xUIElement);
    }
}