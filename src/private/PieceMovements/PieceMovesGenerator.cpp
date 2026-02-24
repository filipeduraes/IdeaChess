#include "PieceMovements/PieceMovesGenerator.h"
#include <Vector2Int.h>

bool PieceMovesGenerator::IsInsideRange(const Vector2Int& pieceIndex)
{
    return pieceIndex.x >= 0 && pieceIndex.x < 8 && pieceIndex.y >= 0 && pieceIndex.y < 8;
}

bool PieceMovesGenerator::IsEmptySquare(const Vector2Int& pieceIndex, const IdeaChess::ChessGame& game)
{
    if (!IsInsideRange(pieceIndex))
    {
        return false;
    }

    const IdeaChess::Piece& square = game.board[pieceIndex.y][pieceIndex.x];
    return square.IsEmpty();
}

bool PieceMovesGenerator::IsCapturablePiece(const Vector2Int& pieceIndex, const IdeaChess::ChessGame& game)
{
    if (!IsInsideRange(pieceIndex) || IsEmptySquare(pieceIndex, game))
    {
        return false;
    }

    const IdeaChess::Piece& square = game.board[pieceIndex.y][pieceIndex.x];
    const bool pieceIsWhite = square.color == IdeaChess::PieceColor::White;
    return pieceIsWhite != game.state.isWhiteTurn;
}
