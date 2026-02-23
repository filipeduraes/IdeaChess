#pragma once
#include <ChessBoardDefinitions.h>
#include <Vector2Int.h>
#include <PieceMovements/PieceMovesGenerator.h>

class PawnMovesGenerator final : public PieceMovesGenerator
{
public:
    virtual void GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves) override;
};