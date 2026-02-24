#pragma once
#include "PieceMovesGenerator.h"

class RookMovesGenerator final : public PieceMovesGenerator
{
public:
    virtual void GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves) override;
};