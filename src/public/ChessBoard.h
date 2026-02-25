#pragma once
#include <ChessBoardDefinitions.h>
#include <Input.h>
#include <string>
#include <PieceMovements/PieceMoves.h>
#include "Vector2Int.h"

class ChessBoard
{
private:
    Vector2Int selectedSquare = -Vector2Int::One();
    Vector2Int focusedSquare = -Vector2Int::One();
    const Input& input;

	const std::string initialPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e4 0 1";
    IdeaChess::Board board = { IdeaChess::Piece() };
    IdeaChess::GameState gameState;
    IdeaChess::Moves selectedPieceMoves;

    PieceMoves pieceMoves;

public:
    explicit ChessBoard(const Input& input);
	void Update();

    void SetFocusedSquareIndex(const Vector2Int& index)
    {
        focusedSquare = index;
    }

    [[nodiscard]] Vector2Int GetSelectedSquare() const
    {
        return selectedSquare;
    }

    const IdeaChess::Moves& GetSelectedPieceMoves()
    {
        return selectedPieceMoves;
    }

    [[nodiscard]] const IdeaChess::Board& GetBoard() const
    {
        return board;
    }

private:
    void SelectPiece();

    void ResetPieceSelection();
    void PerformMovement();

    void HandleCastling();
    void HandleEnPassant();
    void MovePiece(const Vector2Int& from, const Vector2Int& to);

    [[nodiscard]] bool IsPieceTurn(IdeaChess::PieceColor color) const;

    static void ParseFenPosition(const std::string& fenPosition, IdeaChess::Board& outBoard, IdeaChess::GameState& outGameState);
};