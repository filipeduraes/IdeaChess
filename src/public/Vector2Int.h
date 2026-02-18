#pragma once
#include <cstdint>
#include <ostream>

struct Vector2Int
{
public:
    int32_t x = 0;
    int32_t y = 0;

    Vector2Int() = default;

    Vector2Int(int32_t x, int32_t y)
        : x(x),
          y(y)
    {
    }

    Vector2Int(const Vector2Int& vector)
        : x(vector.x),
          y(vector.y)
    {
    }

    static Vector2Int One()
    {
        return Vector2Int(1, 1);
    }

    static Vector2Int Zero()
    {
        return Vector2Int(0, 0);
    }

    Vector2Int operator *(int32_t other)
    {
        return Vector2Int(x * other, y * other);
    }

    Vector2Int operator /(int32_t other)
    {
        return Vector2Int(x / other, y / other);
    }

    Vector2Int operator +(Vector2Int other)
    {
        return Vector2Int(x + other.x, y + other.y);
    }

    Vector2Int operator -()
    {
        return Vector2Int(-x, -y);
    }

    Vector2Int operator -(Vector2Int other)
    {
        return *this + -other;
    }
};

std::ostream& operator<<(std::ostream& os, const Vector2Int& vector);