#pragma once
#include <string>
#include "Vector2Int.h"
#include <Input.h>
#include <PieceMovements/PieceMoves.h>
#include <ChessBoardDefinitions.h>

class ChessBoard
{
private:
    Vector2Int selectedSquare = -Vector2Int::One();
    Vector2Int focusedSquare = -Vector2Int::One();
    const Input& input;

	const std::string initialPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    IdeaChess::Board board = { IdeaChess::Piece() };
    IdeaChess::GameState gameState;
    IdeaChess::Moves selectedPieceMoves;

    PieceMoves pieceMoves;

public:
    ChessBoard(const Input& input);
	void Update();

    void SetFocusedSquareIndex(const Vector2Int& index)
    {
        focusedSquare = index;
    }

    Vector2Int GetSelectedSquare() const
    {
        return selectedSquare;
    }

    const IdeaChess::Moves& GetSelectedPieceMoves()
    {
        return selectedPieceMoves;
    }

    const IdeaChess::Board& GetBoard() const
    {
        return board;
    }

private:
    void SelectPiece();
    void ResetPieceSelection();
    void PerformMovement();

    bool IsPieceTurn(IdeaChess::PieceColor color) const;
    void ParseFenPosition(std::string fenPosition, IdeaChess::Board& outBoard, IdeaChess::GameState& outGameState);
};