#include "PieceMovements/PieceMoves.h"
#include <ChessBoardDefinitions.h>
#include <unordered_map>
#include "PieceMovements/PieceMovesGenerator.h"
#include "PieceMovements/PawnMovesGenerator.h"
#include <Vector2Int.h>
#include <memory>

PieceMoves::PieceMoves()
{
	generators.emplace(IdeaChess::PieceType::Pawn, std::make_unique<PawnMovesGenerator>());
}

void PieceMoves::GenerateMoves(const Vector2Int& pieceIndex, const IdeaChess::ChessGame& game, IdeaChess::Moves& outMoves)
{
	const IdeaChess::Piece& piece = game.board[pieceIndex.y][pieceIndex.x];
	outMoves.clear();

	if (generators.contains(piece.type))
	{
		generators.at(piece.type)->GenerateMoves(pieceIndex, game, outMoves);
	}
}
