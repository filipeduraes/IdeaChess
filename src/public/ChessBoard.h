#pragma once
#include <string>
#include <array>
#include "Vector2Int.h"
#include <vector>
#include <Input.h>

enum class PieceType
{
    None   = 0,
    King   = 1,
    Queen  = 2,
    Bishop = 3,
    Night  = 4,
    Rook   = 5,
    Pawn   = 6
};

enum class PieceColor
{
    None  = 0,
    White = 1,
    Black = 2
};

struct Piece
{
    PieceType type = PieceType::None;
    PieceColor color = PieceColor::None;

    bool IsEmpty() const
    {
        return type == PieceType::None || color == PieceColor::None;
    }
};

struct GameState
{
    bool isWhiteTurn = true;
};

class ChessBoard
{
public:
    using Board = std::array<std::array<Piece, 8>, 8>;

private:
    Vector2Int selectedSquare = -Vector2Int::One();
    Vector2Int focusedSquare = -Vector2Int::One();
    const Input& input;

	const std::string initialPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Board board = { Piece() };
    GameState gameState;

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

    const Board& GetBoard() const
    {
        return board;
    }

private:
    bool IsPieceTurn(PieceColor color) const;
    void GenerateMoves(Vector2Int pieceIndex, std::vector<Vector2Int>& moves);
    void ParseFenPosition(std::string fenPosition, Board& outBoard, GameState& outGameState);
};