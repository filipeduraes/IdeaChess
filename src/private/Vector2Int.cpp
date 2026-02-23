#include <ostream>
#include <Vector2Int.h>

std::ostream& operator<<(std::ostream& os, const Vector2Int& vector)
{
    os << "(" << vector.x << ", " << vector.y << ")";
    return os;
}