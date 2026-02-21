#include "ChessBoard.h"
#include <string>
#include <unordered_map>
#include <cctype>
#include <Vector2Int.h>
#include <cstdint>
#include <vector>
#include <Input.h>

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
			Piece focusedPiece = board[focusedSquare.y][focusedSquare.x];

			if (!focusedPiece.IsEmpty() && IsPieceTurn(focusedPiece.color))
			{
				selectedSquare = focusedSquare;
			}
		}
		else 
		{
			board[focusedSquare.y][focusedSquare.x] = board[selectedSquare.y][selectedSquare.x];
			board[selectedSquare.y][selectedSquare.x] = Piece();
			gameState.isWhiteTurn = !gameState.isWhiteTurn;
			selectedSquare = -Vector2Int::One();
		}
	}
}

bool ChessBoard::IsPieceTurn(PieceColor color) const
{
	return color == PieceColor::White && gameState.isWhiteTurn 
		|| color == PieceColor::Black && !gameState.isWhiteTurn;
}

void ChessBoard::GenerateMoves(Vector2Int pieceIndex, std::vector<Vector2Int>& moves)
{
}

void ChessBoard::ParseFenPosition(std::string fenPosition, ChessBoard::Board& outBoard, GameState& outGameState)
{
	const std::unordered_map<char, PieceType> pieceMapping =
	{
		{'r', PieceType::Rook},
		{'b', PieceType::Bishop},
		{'n', PieceType::Night},
		{'k', PieceType::King},
		{'q', PieceType::Queen},
		{'p', PieceType::Pawn}
	};

	enum class ParseFenStep : uint8_t
	{
		Positions = 0,
		Turn = 1
	};

	Board parsedBoard;
	GameState parsedGameState;

	ParseFenStep currentStep = ParseFenStep::Positions;
	bool isParsingPositions = true;
	bool isParsingTurn = false;
	Vector2Int currentIndex = Vector2Int::Zero();

	for (int i = 0; i < fenPosition.size(); i++)
	{
		if (fenPosition[i] == ' ')
		{
			currentStep = static_cast<ParseFenStep>(static_cast<uint8_t>(currentStep) + 1);
			continue;
		}

		if (currentStep == ParseFenStep::Positions)
		{
			if (fenPosition[i] == '/')
			{
				currentIndex.x = 0;
				currentIndex.y++;
				continue;
			}
			else 
			{
				if (!std::isdigit(fenPosition[i])) 
				{
					PieceColor pieceColor = std::isupper(fenPosition[i]) ? PieceColor::White : PieceColor::Black;
					PieceType pieceType = pieceMapping.at(std::tolower(fenPosition[i]));
					parsedBoard[currentIndex.y][currentIndex.x] = Piece(pieceType, pieceColor);
					currentIndex.x++;
				}
				else 
				{
					int32_t spacing = fenPosition[i] - '0';
					currentIndex.x += spacing;
				}
			}
		}
		else if (currentStep == ParseFenStep::Turn)
		{
			parsedGameState.isWhiteTurn = fenPosition[i] == 'w';
		}
	}

	outBoard = parsedBoard;
	outGameState = parsedGameState;
}
