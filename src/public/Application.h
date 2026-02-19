#pragma once

#include <string>
#include <unordered_set>
#include <Color.h>
#include <memory>
#include <Vector2Int.h>
#include <Renderer.h>
#include <Window.h>
#include <cstdint>
#include <SDL_events.h>
#include "Rect.h"
#include "Texture.h"
#include <vector>

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

class Application
{
private:
    const std::string WindowTitle = "Idea Chess";

    std::unordered_set<SDL_EventType> currentInput;
    Color lightCellColor = Color(0xfab1a0);
    Color darkCellColor = Color(0xe17055);
    Color clearColor = Color(0, 200, 100);
    Color selectionColor = Color(0, 100, 255);
    Color clickedColor = Color(200, 50, 100);

    Vector2Int selectedCell = Vector2Int(-1, -1);

    Vector2Int mousePosition;
    bool hasClicked = false;

    std::vector<PieceData> pieces;

    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Texture> piecesTexture;

public:
    Application();
    ~Application();

    void Run();
    
    void Render();
    void PollInput();
    void DrawBoard();
    void DrawCell(Vector2Int cellIndex, Color color);
    void DrawPieces();
    void DrawPiece(const PieceData& pieceData);

    Rect GetCellRect(Vector2Int cellIndex) const;

    int32_t GetCellSize() const;
    int32_t GetBoardSize() const;
    Vector2Int GetBorderSize() const;
};