#pragma once
#include <cstdint>
#include <ostream>
#include <functional>

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

    static Vector2Int Up()
    {
        return Vector2Int(0, 1);
    }

    static Vector2Int Down()
    {
        return Vector2Int(0, -1);
    }

    static Vector2Int Right()
    {
        return Vector2Int(1, 0);
    }

    static Vector2Int Left()
    {
        return Vector2Int(-1, 0);
    }

    static Vector2Int Zero()
    {
        return Vector2Int(0, 0);
    }

    Vector2Int operator *(int32_t other) const
    {
        return Vector2Int(x * other, y * other);
    }

    Vector2Int operator /(int32_t other) const
    {
        return Vector2Int(x / other, y / other);
    }

    Vector2Int operator +(const Vector2Int& other) const
    {
        return Vector2Int(x + other.x, y + other.y);
    }

    Vector2Int operator -() const
    {
        return Vector2Int(-x, -y);
    }

    Vector2Int operator -(const Vector2Int& other)
    {
        return *this + -other;
    }

    bool operator ==(const Vector2Int& other) const
    {
        return other.x == x && other.y == y;
    }

    bool operator !=(const Vector2Int& other) const
    {
        return other.x != x || other.y != y;
    }

private:
    friend struct std::hash<Vector2Int>;
};

std::ostream& operator<<(std::ostream& os, const Vector2Int& vector);

namespace std
{
    template<>
    struct hash<Vector2Int>
    {
        std::size_t operator()(const Vector2Int& vector) const noexcept
        {
            std::uint64_t packed = (static_cast<std::uint64_t>(static_cast<std::uint32_t>(vector.x)) << 32) 
                                  | static_cast<std::uint32_t>(vector.y);

            return std::hash<std::uint64_t>{}(packed);
        }
    };
}