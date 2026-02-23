#pragma once
#include <array>
#include <unordered_set>
#include <Vector2Int.h>

namespace IdeaChess 
{
    enum class PieceType
    {
        None = 0,
        King = 1,
        Queen = 2,
        Bishop = 3,
        Night = 4,
        Rook = 5,
        Pawn = 6
    };

    enum class PieceColor
    {
        None = 0,
        White = 1,
        Black = 2
    };

    struct Piece
    {
        PieceType type = PieceType::None;
        PieceColor color = PieceColor::None;

        [[nodiscard]] bool IsEmpty() const
        {
            return type == PieceType::None || color == PieceColor::None;
        }
    };

    struct GameState
    {
        bool isWhiteTurn = true;
    };
	
    using Board = std::array<std::array<Piece, 8>, 8>;
    using Moves = std::unordered_set<Vector2Int>;

    struct ChessGame
    {
        const GameState& state;
        const Board& board;

        ChessGame(const GameState& state, const Board& board)
            : state(state),
              board(board)
        {
        }
    };
}