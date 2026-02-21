#pragma once
#include "Vector2Int.h"
#include "Rect.h"
#include <cstdint>
#include "Color.h"
#include "Renderer.h"
#include <Window.h>
#include <memory>
#include "Texture.h"
#include <vector>
#include "Input.h"

enum class PieceType
{
    King = 0,
    Queen = 1,
    Bishop = 2,
    Night = 3,
    Rook = 4,
    Pawn = 5
};

enum class PieceColor
{
    White = 0,
    Black = 1
};

struct PieceData
{
    PieceType type;
    PieceColor color;
    Vector2Int index;
};

class ChessBoardView
{
private:
    Vector2Int selectedCell = Vector2Int(-1, -1);

    Color lightCellColor = Color(0xfab1a0);
    Color darkCellColor = Color(0xe17055);
    Color clearColor = Color(0, 200, 100);
    Color selectionColor = Color(0, 100, 255);
    Color clickedColor = Color(200, 50, 100);

    const Input& input;
    Window* window = nullptr;
    Renderer* renderer = nullptr;

    std::unique_ptr<Texture> piecesTexture = nullptr;
    std::vector<PieceData> pieces;

public:
    ChessBoardView(const Input& input);
    void InitializeRender(Window* inWindow, Renderer* inRenderer);
	void Render();

private:
	void DrawBoard();
	void DrawCell(Vector2Int cellIndex, Color color);
	void DrawPieces();
	void DrawPiece(const PieceData& pieceData);

	Rect GetCellRect(Vector2Int cellIndex) const;
	int32_t GetCellSize() const;
	int32_t GetBoardSize() const;
    Vector2Int GetBorderSize() const;
};