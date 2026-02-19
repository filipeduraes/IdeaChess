#pragma once
#include <cstdint>

struct Color
{
public:
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0;

    Color() = default;

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        : r(r),
          g(g),
          b(b),
          a(a)
    {
    }

    Color(const Color& color)
        : r(color.r),
          g(color.g),
          b(color.b),
          a(color.a)
    {
    }

    Color(uint32_t hexValue) 
        : r((hexValue >> 16) & 0xFF),
          g((hexValue >> 8) & 0xFF),
          b(hexValue & 0xFF),
          a(255)
    {
    }

    bool operator ==(const Color& color) const
    {
        return r == color.r
            && g == color.g
            && b == color.b;
    }
};

namespace Colors
{
    const Color White = Color(255, 255, 255, 255);
    const Color Black = Color(0, 0, 0, 255);
}