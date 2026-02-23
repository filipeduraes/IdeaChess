#include "PieceMovements/PieceMoves.h"
#include <ChessBoardDefinitions.h>
#include <memory>
#include <unordered_map>
#include <Vector2Int.h>

#include "PieceMovements/BishopMovesGenerator.h"
#include "PieceMovements/PawnMovesGenerator.h"
#include "PieceMovements/PieceMovesGenerator.h"

PieceMoves::PieceMoves()
{
	generators.emplace(IdeaChess::PieceType::Pawn, std::make_unique<PawnMovesGenerator>());
	generators.emplace(IdeaChess::PieceType::Bishop, std::make_unique<BishopMovesGenerator>());
}

void PieceMoves::GenerateMoves(const Vector2Int& pieceIndex, const IdeaChess::ChessGame& game, IdeaChess::Moves& outMoves) const
{
	const IdeaChess::Piece& piece = game.board[pieceIndex.y][pieceIndex.x];
	outMoves.clear();

	if (generators.contains(piece.type))
	{
		generators.at(piece.type)->GenerateMoves(pieceIndex, game, outMoves);
	}
}
