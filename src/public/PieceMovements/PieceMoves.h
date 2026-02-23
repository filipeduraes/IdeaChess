#pragma once
#include <ChessBoardDefinitions.h>
#include <memory>
#include <unordered_map>
#include <Vector2Int.h>
#include "PieceMovesGenerator.h"

class PieceMoves
{
private:
	std::unordered_map<IdeaChess::PieceType, std::unique_ptr<PieceMovesGenerator>> generators;

public:
	PieceMoves();
	void GenerateMoves(const Vector2Int& pieceIndex, const IdeaChess::ChessGame& game, IdeaChess::Moves& outMoves) const;
};