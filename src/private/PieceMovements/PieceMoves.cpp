#include "PieceMovements/PieceMoves.h"
#include <ChessBoardDefinitions.h>
#include <memory>
#include <unordered_map>
#include <Vector2Int.h>

#include "PieceMovements/BishopMovesGenerator.h"
#include "PieceMovements/KingMovesGenerator.h"
#include "PieceMovements/NightMovesGenerator.h"
#include "PieceMovements/PawnMovesGenerator.h"
#include "PieceMovements/PieceMovesGenerator.h"
#include "PieceMovements/QueenMovesGenerator.h"
#include "PieceMovements/RookMovesGenerator.h"

PieceMoves::PieceMoves()
{
	generators.emplace(IdeaChess::PieceType::Pawn, std::make_unique<PawnMovesGenerator>());
	generators.emplace(IdeaChess::PieceType::Bishop, std::make_unique<BishopMovesGenerator>());
	generators.emplace(IdeaChess::PieceType::Night, std::make_unique<NightMovesGenerator>());
	generators.emplace(IdeaChess::PieceType::Rook, std::make_unique<RookMovesGenerator>());
	generators.emplace(IdeaChess::PieceType::Queen, std::make_unique<QueenMovesGenerator>());
	generators.emplace(IdeaChess::PieceType::King, std::make_unique<KingMovesGenerator>());
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
