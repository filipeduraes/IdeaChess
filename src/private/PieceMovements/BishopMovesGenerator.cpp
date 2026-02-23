#include "PieceMovements/BishopMovesGenerator.h"

void BishopMovesGenerator::GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves)
{
    uint8_t activeDirections = TopRight | TopLeft | BottomRight | BottomLeft;

    for (int32_t i = 1; i <= 7; i++)
    {
        if (activeDirections == None)
        {
            break;
        }

        if ((activeDirections & TopLeft) != 0 && !EvaluateDirection(pieceIndex + Vector2Int(-i, i), game, moves))
        {
            activeDirections &= ~TopLeft;
        }

        if ((activeDirections & TopRight) != 0 && !EvaluateDirection(pieceIndex + Vector2Int(i, i), game, moves))
        {
            activeDirections &= ~TopRight;
        }

        if ((activeDirections & BottomLeft) != 0 && !EvaluateDirection(pieceIndex + Vector2Int(-i, -i), game, moves))
        {
            activeDirections &= ~BottomLeft;
        }

        if ((activeDirections & BottomRight) != 0 && !EvaluateDirection(pieceIndex + Vector2Int(i, -i), game, moves))
        {
            activeDirections &= ~BottomRight;
        }
    }
}

bool BishopMovesGenerator::EvaluateDirection(const Vector2Int& directionIndex, const IdeaChess::ChessGame& game, IdeaChess::Moves& moves)
{
    if (!IsInsideRange(directionIndex))
    {
        return false;
    }

    if (!game.board[directionIndex.y][directionIndex.x].IsEmpty())
    {
        const bool pieceIsWhite = game.board[directionIndex.y][directionIndex.x].color == IdeaChess::PieceColor::White;

        if (pieceIsWhite != game.state.isWhiteTurn)
        {
            moves.insert(directionIndex);
        }

        return false;
    }

    moves.insert(directionIndex);
    return true;
}
