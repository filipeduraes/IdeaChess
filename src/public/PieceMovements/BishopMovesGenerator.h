#pragma once
#include "PieceMovesGenerator.h"

class BishopMovesGenerator final : public PieceMovesGenerator
{
private:
    enum GeneratorDirection : uint8_t
    {
        None        = 0,
        TopRight    = 1 << 0,
        TopLeft     = 1 << 1,
        BottomRight = 1 << 2,
        BottomLeft  = 1 << 3
    };

public:
    virtual void GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves) override;

    static bool EvaluateDirection(const Vector2Int& directionIndex, const IdeaChess::ChessGame& game, IdeaChess::Moves& moves);
};
