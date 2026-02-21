#include "ChessBoard.h"
#include <string>
#include <unordered_map>
#include <cctype>
#include <Vector2Int.h>
#include <cstdint>
#include <vector>
#include <Input.h>
#include <algorithm>

ChessBoard::ChessBoard(const Input& input)
	: input(input)
{
	board = ParseFenPosition(initialPosition);
}

void ChessBoard::Update()
{
	if (input.IsMouseButtonDown(MouseButton::Left) && focusedSquare.x >= 0)
	{
		if (selectedSquare.x < 0)
		{
			if (!board[focusedSquare.y][focusedSquare.x].IsEmpty()) 
			{
				selectedSquare = focusedSquare;
			}
		}
		else 
		{
			board[focusedSquare.y][focusedSquare.x] = board[selectedSquare.y][selectedSquare.x];
			board[selectedSquare.y][selectedSquare.x] = Piece();
			selectedSquare = -Vector2Int::One();
		}
	}
}

void ChessBoard::GenerateMoves(Vector2Int pieceIndex, std::vector<Vector2Int>& moves)
{
}

ChessBoard::Board ChessBoard::ParseFenPosition(std::string fenPosition)
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

	Board parsedBoard;
	bool isParsingPositions = true;
	Vector2Int currentIndex = Vector2Int::Zero();

	for (int i = 0; i < fenPosition.size(); i++)
	{
		if (isParsingPositions)
		{
			if (fenPosition[i] == ' ')
			{
				isParsingPositions = false;
			}
			else if (fenPosition[i] == '/')
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
	}

	return parsedBoard;
}
