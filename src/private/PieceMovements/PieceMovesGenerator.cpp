#include "PieceMovements/PieceMovesGenerator.h"
#include <Vector2Int.h>

bool PieceMovesGenerator::IsInsideRange(const Vector2Int& pieceIndex)
{
    return pieceIndex.x >= 0 && pieceIndex.x < 8 && pieceIndex.y >= 0 && pieceIndex.y < 8;
}
