#include "ChessBoard.h"
#include <cctype>
#include <ChessBoardDefinitions.h>
#include <Input.h>
#include <string>
#include <unordered_map>
#include <Vector2Int.h>

ChessBoard::ChessBoard(const Input& input)
	: input(input)
{
	ParseFenPosition(initialPosition, board, gameState);
}

void ChessBoard::Update()
{
	if (input.IsMouseButtonDown(MouseButton::Left) && focusedSquare.x >= 0)
	{
		if (selectedSquare.x < 0)
		{
			const IdeaChess::Piece focusedPiece = board[focusedSquare.y][focusedSquare.x];

			if (!focusedPiece.IsEmpty() && IsPieceTurn(focusedPiece.color))
			{
				SelectPiece();
			}
		}
		else 
		{
			if (selectedSquare == focusedSquare)
			{
				ResetPieceSelection();
				return;
			}

			PerformMovement();
		}
	}
}

void ChessBoard::ResetPieceSelection()
{
	selectedSquare = -Vector2Int::One();
	selectedPieceMoves.clear();
}

void ChessBoard::SelectPiece()
{
	selectedSquare = focusedSquare;
	pieceMoves.GenerateMoves(selectedSquare, IdeaChess::ChessGame(gameState, board), selectedPieceMoves);
}

void ChessBoard::PerformMovement()
{
	if (!selectedPieceMoves.contains(focusedSquare))
	{
		ResetPieceSelection();
		return;
	}

    HandleCastling();
    HandleEnPassant();

    MovePiece(selectedSquare, focusedSquare);
	gameState.isWhiteTurn = !gameState.isWhiteTurn;
	ResetPieceSelection();
}

void ChessBoard::HandleCastling()
{
    const IdeaChess::Piece sourcePiece = board[selectedSquare.y][selectedSquare.x];

    if (gameState.CanCastle())
    {
        if (sourcePiece.type == IdeaChess::PieceType::King)
        {
            if (selectedSquare.y == focusedSquare.y)
            {
                const int32_t sourceToDestination = focusedSquare.x - selectedSquare.x;

                if (sourceToDestination == -2 && gameState.CanQueenCastle())
                {
                    MovePiece(Vector2Int(0, selectedSquare.y), Vector2Int(selectedSquare.x - 1, selectedSquare.y)); // Move Rook
                }
                else if (sourceToDestination == 2 && gameState.CanKingCastle())
                {
                    MovePiece(Vector2Int(7, selectedSquare.y), Vector2Int(selectedSquare.x + 1, selectedSquare.y)); // Move Rook
                }
            }

            gameState.DisableCastlingForCurrentColor();
        }
        else if (sourcePiece.type == IdeaChess::PieceType::Rook)
        {
            if (selectedSquare.x == 0)
            {
                gameState.queenSideCastlingAvailable = 0;
            }
            else if (selectedSquare.x == 7)
            {
                gameState.kingSideCastlingAvailable = 0;
            }
        }
    }
}

void ChessBoard::HandleEnPassant()
{
    const IdeaChess::Piece sourcePiece = board[selectedSquare.y][selectedSquare.x];

    if (sourcePiece.type == IdeaChess::PieceType::Pawn)
    {
        const int32_t enPassantPieceDisplacement = gameState.isWhiteTurn ? 1 : -1;

        if (focusedSquare == gameState.availableEnPassantIndex) //Handle active en passant capture
        {
            board[gameState.availableEnPassantIndex.y + enPassantPieceDisplacement][gameState.availableEnPassantIndex.x] = IdeaChess::Piece();
            gameState.availableEnPassantIndex = -Vector2Int::One();
        }
        else if (std::abs(focusedSquare.y - selectedSquare.y) == 2) //Handle new en passant candidate
        {
            gameState.availableEnPassantIndex = selectedSquare + Vector2Int::Down() * enPassantPieceDisplacement;
            return;
        }
    }

    gameState.availableEnPassantIndex = -Vector2Int::One();
}

void ChessBoard::MovePiece(const Vector2Int& from, const Vector2Int& to)
{
    board[to.y][to.x] = board[from.y][from.x];
    board[from.y][from.x] = IdeaChess::Piece();
}

bool ChessBoard::IsPieceTurn(const IdeaChess::PieceColor color) const
{
	return color == IdeaChess::PieceColor::White && gameState.isWhiteTurn
		|| color == IdeaChess::PieceColor::Black && !gameState.isWhiteTurn;
}

void ChessBoard::ParseFenPosition(const std::string& fenPosition, IdeaChess::Board& outBoard, IdeaChess::GameState& outGameState)
{
	const std::unordered_map<char, IdeaChess::PieceType> pieceMapping =
	{
		{'r', IdeaChess::PieceType::Rook},
		{'b', IdeaChess::PieceType::Bishop},
		{'n', IdeaChess::PieceType::Night},
		{'k', IdeaChess::PieceType::King},
		{'q', IdeaChess::PieceType::Queen},
		{'p', IdeaChess::PieceType::Pawn}
	};

	enum class ParseFenStep : uint8_t
	{
		Positions = 0,
		Turn = 1,
	    Castling = 2,
	    EnPassant = 3
	};

	IdeaChess::Board parsedBoard;
	IdeaChess::GameState parsedGameState;
    parsedGameState.kingSideCastlingAvailable = 0;
    parsedGameState.queenSideCastlingAvailable = 0;

	ParseFenStep currentStep = ParseFenStep::Positions;
	Vector2Int currentIndex = Vector2Int::Zero();
    char enPassantSquareLetter = -1;

	for (const char character : fenPosition)
	{
		if (character == ' ')
		{
			currentStep = static_cast<ParseFenStep>(static_cast<uint8_t>(currentStep) + 1);
			continue;
		}

		if (currentStep == ParseFenStep::Positions)
		{
			if (character == '/')
			{
				currentIndex.x = 0;
				currentIndex.y++;
				continue;
			}

		    if (!std::isdigit(character))
            {
                const IdeaChess::PieceColor pieceColor = std::isupper(character) ? IdeaChess::PieceColor::White : IdeaChess::PieceColor::Black;
		        char lowerCharacter = static_cast<char>(std::tolower(character));
                const IdeaChess::PieceType pieceType = pieceMapping.at(lowerCharacter);

                parsedBoard[currentIndex.y][currentIndex.x] = IdeaChess::Piece(pieceType, pieceColor);
                currentIndex.x++;
            }
		    else
            {
                const int32_t spacing = character - '0';
                currentIndex.x += spacing;
            }
        }
		else if (currentStep == ParseFenStep::Turn)
		{
			parsedGameState.isWhiteTurn = character == 'w';
		}
	    else if (currentStep == ParseFenStep::Castling)
	    {
            const IdeaChess::PieceColor sideColor = std::isupper(character) ? IdeaChess::PieceColor::White : IdeaChess::PieceColor::Black;
		    const char lowerCharacter = static_cast<char>(std::tolower(character));

	        if (lowerCharacter == 'k')
	        {
	            parsedGameState.kingSideCastlingAvailable |= static_cast<uint8_t>(sideColor);
	        }
	        else
	        {
	            parsedGameState.queenSideCastlingAvailable |= static_cast<uint8_t>(sideColor);
	        }
	    }
	    else if (currentStep == ParseFenStep::EnPassant)
	    {
            if (!std::isdigit(character))
            {
                enPassantSquareLetter = character;
            }
	        else
	        {
	            parsedGameState.availableEnPassantIndex = Vector2Int(enPassantSquareLetter - 'a', 8 - character - '0');
	        }
	    }
	}

	outBoard = parsedBoard;
	outGameState = parsedGameState;
}