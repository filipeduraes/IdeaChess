#include <ChessBoardDefinitions.h>
#include <Vector2Int.h>
#include <PieceMovements/PawnMovesGenerator.h>

void PawnMovesGenerator::GenerateMoves(const Vector2Int& pieceIndex, const IdeaChess::ChessGame game, IdeaChess::Moves& moves)
{
	const IdeaChess::Piece& piece = game.board[pieceIndex.y][pieceIndex.x];

	const bool isWhitePawn = piece.color == IdeaChess::PieceColor::White;
	const bool isWhitePawnFirstMove = isWhitePawn && pieceIndex.y == 6;
	const bool isBlackPawnFirstMove = !isWhitePawn && pieceIndex.y == 1;

	const Vector2Int pawnMoveDirection = isWhitePawn ? Vector2Int::Down() : Vector2Int::Up();
	const Vector2Int pawnFirstMove = pieceIndex + pawnMoveDirection;

	if (IsInsideRange(pawnFirstMove) && game.board[pawnFirstMove.y][pawnFirstMove.x].IsEmpty())
	{
		moves.insert(pawnFirstMove);
	}

	if (isWhitePawnFirstMove || isBlackPawnFirstMove)
	{
		const Vector2Int pawnSecondMove = pieceIndex + pawnMoveDirection * 2;

		if (IsInsideRange(pawnSecondMove) && game.board[pawnSecondMove.y][pawnSecondMove.x].IsEmpty())
		{
			moves.insert(pawnSecondMove);
		}
	}

	const Vector2Int rightCaptureMove = pieceIndex + pawnMoveDirection + Vector2Int::Right();
	const Vector2Int leftCaptureMove = pieceIndex + pawnMoveDirection + Vector2Int::Left();

	if (IsInsideRange(rightCaptureMove) && !game.board[rightCaptureMove.y][rightCaptureMove.x].IsEmpty())
	{
		moves.insert(rightCaptureMove);
	}

	if (IsInsideRange(leftCaptureMove) && !game.board[leftCaptureMove.y][leftCaptureMove.x].IsEmpty())
	{
		moves.insert(leftCaptureMove);
	}
}