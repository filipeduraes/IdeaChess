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

	board[focusedSquare.y][focusedSquare.x] = board[selectedSquare.y][selectedSquare.x];
	board[selectedSquare.y][selectedSquare.x] = IdeaChess::Piece();
	gameState.isWhiteTurn = !gameState.isWhiteTurn;
	ResetPieceSelection();
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
		Turn = 1
	};

	IdeaChess::Board parsedBoard;
	IdeaChess::GameState parsedGameState;

	ParseFenStep currentStep = ParseFenStep::Positions;
	Vector2Int currentIndex = Vector2Int::Zero();

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
	}

	outBoard = parsedBoard;
	outGameState = parsedGameState;
}