#pragma once
#include <cstdint>
#include <memory>
#include <Window.h>
#include "ChessBoard.h"
#include "ChessBoardDefinitions.h"
#include "Color.h"
#include "Input.h"
#include "Rect.h"
#include "Renderer.h"
#include "Texture.h"
#include "Vector2Int.h"

class ChessBoardView
{
private:
    Color lightCellColor = Color(0xfab1a0);
    Color darkCellColor = Color(0xe17055);
    Color clearColor = Color(0x58B19F);
    Color selectionColor = Color(0x1B9CFC);
    Color clickedColor = Color(0xEAB543);
    Color moveColor = Color(0xF8EFBA);
    Color captureColor = Color(0xFC427B);

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
	void DrawBoard() const;
	void DrawCell(const Vector2Int& cellIndex, const Color& color) const;
	void DrawPieces() const;
    void DrawPiece(const IdeaChess::Piece& piece, const Vector2Int& index) const;

	[[nodiscard]] Rect GetCellRect(const Vector2Int& cellIndex) const;
	[[nodiscard]] int32_t GetCellSize() const;
	[[nodiscard]] int32_t GetBoardSize() const;
    [[nodiscard]] Vector2Int GetBorderSize() const;
};