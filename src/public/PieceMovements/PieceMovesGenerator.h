#pragma once
#include <ChessBoardDefinitions.h>
#include <Vector2Int.h>

class PieceMovesGenerator
{
public:
    virtual ~PieceMovesGenerator() = default;

    virtual void GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves) = 0;

    static bool IsInsideRange(const Vector2Int& pieceIndex);
    static bool IsEmptySquare(const Vector2Int& pieceIndex, const IdeaChess::ChessGame& game);
    static bool IsCapturablePiece(const Vector2Int& pieceIndex, const IdeaChess::ChessGame& game);
};