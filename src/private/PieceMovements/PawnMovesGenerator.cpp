#include <PieceMovements/PawnMovesGenerator.h>
#include <Vector2Int.h>
#include <ChessBoardDefinitions.h>

void PawnMovesGenerator::GenerateMoves(const Vector2Int& pieceIndex, IdeaChess::ChessGame game, IdeaChess::Moves& moves)
{
	const IdeaChess::Piece& piece = game.board[pieceIndex.y][pieceIndex.x];

	bool isWhitePawn = piece.color == IdeaChess::PieceColor::White;
	bool isWhitePawnFirstMove = isWhitePawn && pieceIndex.y == 6;
	bool isBlackPawnFirstMove = !isWhitePawn && pieceIndex.y == 1;

	Vector2Int pawnMoveDirection = isWhitePawn ? Vector2Int::Down() : Vector2Int::Up();
	Vector2Int pawnFirstMove = pieceIndex + pawnMoveDirection;

	if (IsInsideRange(pawnFirstMove) && game.board[pawnFirstMove.y][pawnFirstMove.x].IsEmpty())
	{
		moves.insert(pawnFirstMove);
	}

	if (isWhitePawnFirstMove || isBlackPawnFirstMove)
	{
		Vector2Int pawnSecondMove = pieceIndex + pawnMoveDirection * 2;

		if (IsInsideRange(pawnSecondMove) && game.board[pawnSecondMove.y][pawnSecondMove.x].IsEmpty())
		{
			moves.insert(pawnSecondMove);
		}
	}

	Vector2Int rightCaptureMove = pieceIndex + pawnMoveDirection + Vector2Int::Right();
	Vector2Int leftCaptureMove = pieceIndex + pawnMoveDirection + Vector2Int::Left();

	if (IsInsideRange(rightCaptureMove) && !game.board[rightCaptureMove.y][rightCaptureMove.x].IsEmpty())
	{
		moves.insert(rightCaptureMove);
	}

	if (IsInsideRange(leftCaptureMove) && !game.board[leftCaptureMove.y][leftCaptureMove.x].IsEmpty())
	{
		moves.insert(leftCaptureMove);
	}
}