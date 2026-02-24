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

	if (IsEmptySquare(pawnFirstMove, game))
	{
		moves.insert(pawnFirstMove);
	}

	if (isWhitePawnFirstMove || isBlackPawnFirstMove)
	{
		const Vector2Int pawnSecondMove = pieceIndex + pawnMoveDirection * 2;

		if (IsEmptySquare(pawnSecondMove, game))
		{
			moves.insert(pawnSecondMove);
		}
	}

	const Vector2Int rightCaptureMove = pieceIndex + pawnMoveDirection + Vector2Int::Right();
	const Vector2Int leftCaptureMove = pieceIndex + pawnMoveDirection + Vector2Int::Left();

	if (IsCapturablePiece(rightCaptureMove, game))
	{
		moves.insert(rightCaptureMove);
	}

	if (IsCapturablePiece(leftCaptureMove, game))
	{
		moves.insert(leftCaptureMove);
	}
}