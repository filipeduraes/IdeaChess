#include <array>
#include <memory>
#include <cstdint>

#include <ChessBoardView.h>
#include <Renderer.h>
#include <Rect.h>
#include <Window.h>
#include <Texture.h>
#include <algorithm>
#include <Input.h>
#include <Vector2Int.h>
#include <Color.h>
#include <ChessBoard.h>

ChessBoardView::ChessBoardView(ChessBoard& chessBoard, const Input& input)
    : input(input),
      chessBoard(chessBoard)
{
}

void ChessBoardView::InitializeRender(Window* inWindow, Renderer* inRenderer)
{
    window = inWindow;
    renderer = inRenderer;

    renderer->SetClearColor(clearColor);

    piecesTexture = std::make_unique<Texture>(renderer->LoadTexture("../assets/pieces/pieces.png"));
}

void ChessBoardView::Render()
{
    renderer->Clear();

    DrawBoard();

    if (window->IsFocused())
    {
        Vector2Int index = (input.GetMousePosition() - GetBorderSize()) / GetCellSize();
        index.x = std::clamp(index.x, 0, 7);
        index.y = std::clamp(index.y, 0, 7);

        chessBoard.SetFocusedSquareIndex(index);

        DrawCell(index, selectionColor);
    }

    if (chessBoard.GetSelectedSquare().x >= 0)
    {
        DrawCell(chessBoard.GetSelectedSquare(), clickedColor);
    }

    DrawPieces();

    renderer->Render();
}

void ChessBoardView::DrawBoard()
{
    for (int32_t y = 0; y < 8; y++)
    {
        for (int32_t x = 0; x < 8; x++)
        {
            const bool isDark = ((x + y) % 2) != 0;
            Color currentCellColor = isDark ? darkCellColor : lightCellColor;
            DrawCell(Vector2Int(x, y), currentCellColor);
        }
    }
}

void ChessBoardView::DrawCell(Vector2Int cellIndex, Color color)
{
    renderer->DrawRect(GetCellRect(cellIndex), color);
}

void ChessBoardView::DrawPieces()
{
    const ChessBoard::Board& board = chessBoard.GetBoard();

    for (int y = 0; y < board.size(); y++)
    {
        for (int x = 0; x < board[y].size(); x++)
        {
            DrawPiece(board[y][x], Vector2Int(x, y));
        }
    }
}

void ChessBoardView::DrawPiece(const Piece& piece, Vector2Int index)
{
    int32_t pieceSize = piecesTexture->GetSize().x / 6;
    Vector2Int sourceOrigin = Vector2Int(static_cast<int32_t>(piece.type) - 1, static_cast<int32_t>(piece.color) - 1) * pieceSize;
    Vector2Int sourceSize = { pieceSize, pieceSize };

    renderer->DrawTexture(*piecesTexture, Rect(sourceOrigin, sourceSize), GetCellRect(index));
}

Rect ChessBoardView::GetCellRect(Vector2Int cellIndex) const
{
    Vector2Int cellSize = Vector2Int::One() * GetCellSize();
    const Vector2Int cellPosition = GetBorderSize() + (cellIndex * GetCellSize());
    return Rect(cellPosition, cellSize);
}

int32_t ChessBoardView::GetCellSize() const
{
    const int32_t windowSize = std::min(window->GetSize().x, window->GetSize().y);
    const int32_t cellSize = windowSize / 8;

    return cellSize;
}

int32_t ChessBoardView::GetBoardSize() const
{
    return GetCellSize() * 8;
}

Vector2Int ChessBoardView::GetBorderSize() const
{
    const Vector2Int windowSize = window->GetSize();
    const int32_t borderWidth = (windowSize.x - GetBoardSize()) / 2;
    const int32_t borderHeight = (windowSize.y - GetBoardSize()) / 2;

    return Vector2Int(borderWidth, borderHeight);
}