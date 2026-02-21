#include <ChessBoardView.h>
#include <Renderer.h>
#include <Rect.h>
#include <Window.h>
#include <memory>
#include <Texture.h>
#include <algorithm>
#include <Input.h>
#include <Vector2Int.h>
#include <cstdint>
#include <Color.h>

ChessBoardView::ChessBoardView(const Input& input)
    : input(input)
{
}

void ChessBoardView::InitializeRender(Window* inWindow, Renderer* inRenderer)
{
    window = inWindow;
    renderer = inRenderer;

    renderer->SetClearColor(clearColor);

    piecesTexture = std::make_unique<Texture>(renderer->LoadTexture("../assets/pieces/pieces.png"));

    pieces =
    {
        { PieceType::Rook, PieceColor::Black, {0, 0} },
        { PieceType::Night, PieceColor::Black, {1, 0} },
        { PieceType::Bishop, PieceColor::Black, {2, 0} },
        { PieceType::Queen, PieceColor::Black, {3, 0} },
        { PieceType::King, PieceColor::Black, {4, 0} },
        { PieceType::Bishop, PieceColor::Black, {5, 0} },
        { PieceType::Night, PieceColor::Black, {6, 0} },
        { PieceType::Rook, PieceColor::Black, {7, 0} },

        { PieceType::Rook, PieceColor::White, {0, 7} },
        { PieceType::Night, PieceColor::White, {1, 7} },
        { PieceType::Bishop, PieceColor::White, {2, 7} },
        { PieceType::Queen, PieceColor::White, {3, 7} },
        { PieceType::King, PieceColor::White, {4, 7} },
        { PieceType::Bishop, PieceColor::White, {5, 7} },
        { PieceType::Night, PieceColor::White, {6, 7} },
        { PieceType::Rook, PieceColor::White, {7, 7} }
    };

    for (int i = 0; i < 8; i++)
    {
        pieces.push_back({ PieceType::Pawn, PieceColor::Black, {i, 1} });
        pieces.push_back({ PieceType::Pawn, PieceColor::White, {i, 6} });
    }
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

        DrawCell(index, selectionColor);

        if (input.IsMouseButtonDown(MouseButton::Left))
        {
            if (selectedCell.x < 0)
            {
                selectedCell = index;
            }
            else
            {
                selectedCell = Vector2Int(-1, -1);
            }
        }
    }

    if (selectedCell.x >= 0)
    {
        DrawCell(selectedCell, clickedColor);
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
    for (const PieceData& piece : pieces)
    {
        DrawPiece(piece);
    }
}

void ChessBoardView::DrawPiece(const PieceData& pieceData)
{
    int32_t pieceSize = piecesTexture->GetSize().x / 6;
    Vector2Int sourceOrigin = Vector2Int(static_cast<int32_t>(pieceData.type), static_cast<int32_t>(pieceData.color)) * pieceSize;
    Vector2Int sourceSize = { pieceSize, pieceSize };

    renderer->DrawTexture(*piecesTexture, Rect(sourceOrigin, sourceSize), GetCellRect(pieceData.index));
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