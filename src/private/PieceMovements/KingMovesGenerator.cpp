#include <PieceMovements/KingMovesGenerator.h>
#include <cstdint>

void KingMovesGenerator::GenerateMoves(const Vector2Int& pieceIndex, const IdeaChess::ChessGame game, IdeaChess::Moves& moves)
{
    for (int32_t i = -1; i <= 1; i++)
    {
        for (int32_t j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            const Vector2Int candidateIndex = pieceIndex + Vector2Int(i, j);

            if (IsEmptySquare(candidateIndex, game) || IsCapturablePiece(candidateIndex, game))
            {
                moves.insert(candidateIndex);
            }
        }
    }

    if (game.state.CanQueenCastle())
    {
        const bool isQueenSideClear = IsEmptySquare(pieceIndex + Vector2Int::Left(), game)
                                  &&  IsEmptySquare(pieceIndex + Vector2Int::Left() * 2, game)
                                  &&  IsEmptySquare(pieceIndex + Vector2Int::Left() * 3, game);

        if (isQueenSideClear)
        {
            moves.insert(pieceIndex + Vector2Int::Left() * 2);
        }
    }

    if (game.state.CanKingCastle())
    {
        const bool isKingSideClear = IsEmptySquare(pieceIndex + Vector2Int::Right(), game)
                                 &&  IsEmptySquare(pieceIndex + Vector2Int::Right() * 2, game);

        if (isKingSideClear)
        {
            moves.insert(pieceIndex + Vector2Int::Right() * 2);
        }
    }
}
