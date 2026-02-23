#include <PieceMovements/NightMovesGenerator.h>

void NightMovesGenerator::GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves)
{
    struct Offset
    {
        int deltaX;
        int deltaY;
    };

    constexpr std::array knightOffsets =
    {
        Offset{ -2, -1 },
        Offset{ -2,  1 },
        Offset{ -1, -2 },
        Offset{ -1,  2 },
        Offset{  1, -2 },
        Offset{  1,  2 },
        Offset{  2, -1 },
        Offset{  2,  1 }
    };

    for (const Offset& offset : knightOffsets)
    {
        Vector2Int candidateIndex = pieceIndex + Vector2Int(offset.deltaX, offset.deltaY);

        if (IsInsideRange(candidateIndex))
        {
            if (!IsEmptySquare(candidateIndex, game) && !IsCapturablePiece(candidateIndex, game))
            {
                continue;
            }

            moves.insert(candidateIndex);
        }
    }
}