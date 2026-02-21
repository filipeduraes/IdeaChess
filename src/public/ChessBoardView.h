#pragma once
#include "Vector2Int.h"
#include "Rect.h"
#include <cstdint>
#include "Color.h"
#include "Renderer.h"
#include <Window.h>
#include <memory>
#include "Texture.h"
#include "Input.h"
#include "ChessBoard.h"

class ChessBoardView
{
private:
    Color lightCellColor = Color(0xfab1a0);
    Color darkCellColor = Color(0xe17055);
    Color clearColor = Color(0, 200, 100);
    Color selectionColor = Color(0, 100, 255);
    Color clickedColor = Color(200, 50, 100);

    const Input& input;
    ChessBoard& chessBoard;

    Window* window = nullptr;
    Renderer* renderer = nullptr;

    std::unique_ptr<Texture> piecesTexture = nullptr;

public:
    ChessBoardView(ChessBoard& chessBoard, const Input& input);
    void InitializeRender(Window* inWindow, Renderer* inRenderer);
	void Render();

private:
	void DrawBoard();
	void DrawCell(Vector2Int cellIndex, Color color);
	void DrawPieces();
    void DrawPiece(const Piece& piece, Vector2Int index);

	Rect GetCellRect(Vector2Int cellIndex) const;
	int32_t GetCellSize() const;
	int32_t GetBoardSize() const;
    Vector2Int GetBorderSize() const;
};