#pragma once
#include <string>
#include <array>

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
};

class ChessBoard
{
public:
    using Board = std::array<std::array<Piece, 8>, 8>;

private:
	const std::string initialPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    Board board = { Piece() };

public:
    ChessBoard();
	void Update();

    const Board& GetBoard() const
    {
        return board;
    }

private:
    Board ParseFenPosition(std::string fenPosition);
};