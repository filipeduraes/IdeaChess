#pragma once
#include <Vector2Int.h>
#include <ChessBoardDefinitions.h>

class PieceMovesGenerator
{
public:
	virtual void GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves) = 0;

	bool IsInsideRange(const Vector2Int& pieceIndex);
};