#pragma once

#include "WindowSize.h"

namespace Utils
{
    template <typename T>
    static constexpr T DPIAware(T xValue, const WindowSize &xWindowSize) noexcept{
        return xValue;
    }
}