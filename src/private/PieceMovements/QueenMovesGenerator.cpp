#include <PieceMovements/QueenMovesGenerator.h>

#include "PieceMovements/BishopMovesGenerator.h"
#include "PieceMovements/RookMovesGenerator.h"

void QueenMovesGenerator::GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves)
{
    BishopMovesGenerator bishopMovesGenerator = BishopMovesGenerator();
    RookMovesGenerator rookMovesGenerator = RookMovesGenerator();

    bishopMovesGenerator.GenerateMoves(pieceIndex, game, moves);
    rookMovesGenerator.GenerateMoves(pieceIndex, game, moves);
}
