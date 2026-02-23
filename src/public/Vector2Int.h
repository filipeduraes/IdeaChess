#pragma once
#include <cstdint>
#include <functional>
#include <ostream>

struct Vector2Int
{
public:
    int32_t x = 0;
    int32_t y = 0;

    Vector2Int() = default;

    Vector2Int(const int32_t x, const int32_t y)
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
        return { 1, 1 };
    }

    static Vector2Int Up()
    {
        return { 0, 1 };
    }

    static Vector2Int Down()
    {
        return { 0, -1 };
    }

    static Vector2Int Right()
    {
        return { 1, 0 };
    }

    static Vector2Int Left()
    {
        return { -1, 0 };
    }

    static Vector2Int Zero()
    {
        return { 0, 0 };
    }

    Vector2Int operator *(const int32_t other) const
    {
        return { x * other, y * other };
    }

    Vector2Int operator /(const int32_t other) const
    {
        return { x / other, y / other };
    }

    Vector2Int operator +(const Vector2Int& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vector2Int operator -() const
    {
        return { -x, -y };
    }

    Vector2Int operator -(const Vector2Int& other) const
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

template<>
struct std::hash<Vector2Int>
{
    std::size_t operator()(const Vector2Int& vector) const noexcept
    {
        const std::uint64_t packed = static_cast<std::uint64_t>(static_cast<std::uint32_t>(vector.x)) << 32
                                   | static_cast<std::uint32_t>(vector.y);

        return std::hash<std::uint64_t>{}(packed);
    }
};