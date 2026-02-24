#include <PieceMovements/RookMovesGenerator.h>
#include <array>

void RookMovesGenerator::GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves)
{
    const std::array directions = { Vector2Int::Up(), Vector2Int::Right(), Vector2Int::Down(), Vector2Int::Left() };

    for (const Vector2Int& direction : directions)
    {
        for (int32_t i = 1; i < 8; i++)
        {
            Vector2Int candidateIndex = pieceIndex + direction * i;

            if (!IsInsideRange(candidateIndex))
            {
                break;
            }

            if (IsEmptySquare(candidateIndex, game))
            {
                moves.insert(candidateIndex);
                continue;
            }

            if (IsCapturablePiece(candidateIndex, game))
            {
                moves.insert(candidateIndex);
            }

            break;
        }
    }
}
