#pragma once
#include <PieceMovements/PieceMovesGenerator.h>
#include <Vector2Int.h>
#include <ChessBoardDefinitions.h>

class PawnMovesGenerator : public PieceMovesGenerator
{
public:
	virtual void GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves) override;
};