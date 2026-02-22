#pragma once
#include <ChessBoardDefinitions.h>
#include <Vector2Int.h>
#include "PieceMovesGenerator.h"
#include <unordered_map>
#include <memory>

class PieceMoves
{
private:
	std::unordered_map<IdeaChess::PieceType, std::unique_ptr<PieceMovesGenerator>> generators;

public:
	PieceMoves();
	void GenerateMoves(const Vector2Int& pieceIndex, const IdeaChess::ChessGame& game, IdeaChess::Moves& outMoves);
};