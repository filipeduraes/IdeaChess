#pragma once
#include <array>
#include <unordered_set>
#include <Vector2Int.h>

namespace IdeaChess 
{
    enum class PieceType : uint8_t
    {
        None = 0,
        King = 1,
        Queen = 2,
        Bishop = 3,
        Night = 4,
        Rook = 5,
        Pawn = 6
    };

    enum class PieceColor : uint8_t
    {
        None = 0,
        White = 1 << 0,
        Black = 1 << 1
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
        Vector2Int availableEnPassantIndex = -Vector2Int::One();

        uint8_t kingSideCastlingAvailable = static_cast<uint8_t>(PieceColor::White)
                                          | static_cast<uint8_t>(PieceColor::Black);

        uint8_t queenSideCastlingAvailable = static_cast<uint8_t>(PieceColor::White)
                                           | static_cast<uint8_t>(PieceColor::Black);

        [[nodiscard]] PieceColor GetCurrentColorTurn() const
        {
            return isWhiteTurn ? PieceColor::White : PieceColor::Black;
        }

        bool CanCastle() const
        {
            return CanKingCastle() || CanQueenCastle();
        }

        bool CanKingCastle() const
        {
            return (kingSideCastlingAvailable & static_cast<uint8_t>(GetCurrentColorTurn())) != 0;
        }

        bool CanQueenCastle() const
        {
            return (queenSideCastlingAvailable & static_cast<uint8_t>(GetCurrentColorTurn())) != 0;
        }

        void DisableCastlingForCurrentColor()
        {
            queenSideCastlingAvailable &= ~static_cast<uint8_t>(GetCurrentColorTurn());
            kingSideCastlingAvailable &= ~static_cast<uint8_t>(GetCurrentColorTurn());
        }
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