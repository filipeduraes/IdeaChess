#include <Application.h>
#include <memory>
#include <Renderer.h>
#include <Vector2Int.h>
#include <Window.h>
#include <SDL_timer.h>
#include <cstdint>
#include <algorithm>
#include <SDL.h>
#include <SDL_events.h>
#include <Color.h>
#include <SDL_video.h>
#include <SDL_image.h>
#include <Rect.h>
#include <Texture.h>
#include <vector>

Application::Application()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_PNG) != 0)
    {
        return;
    }

    window = std::make_unique<Window>(WindowTitle, Vector2Int(700, 700));
    renderer = std::make_unique<Renderer>(window->CreateRenderer());
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

Application::~Application()
{
    SDL_Quit();
    IMG_Quit();
}

void Application::Run()
{
    renderer->SetClearColor(clearColor);

    if (!piecesTexture->IsLoaded())
    {
        return;
    }

    while (true)
    {
        PollInput();

        if (currentInput.contains(SDL_EventType::SDL_QUIT))
        {
            break;
        }

        renderer->Clear();

        DrawBoard();

        if (window->IsFocused()) 
        {
            Vector2Int index = (mousePosition - GetBorderSize()) / GetCellSize();
            index.x = std::clamp(index.x, 0, 7);
            index.y = std::clamp(index.y, 0, 7);

            DrawCell(index, selectionColor);
        }

        DrawPieces();

        renderer->Render();
        SDL_Delay(1);
    }
}

void Application::PollInput()
{
    currentInput = {};
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        mousePosition = Vector2Int(event.motion.x, event.motion.y);
        currentInput.insert(static_cast<SDL_EventType>(event.type));
        
        bool windowResized = event.window.event == SDL_WINDOWEVENT_RESIZED || event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED;

        if (windowResized)
        {
            window->UpdateSize();
        }
    }
}

void Application::DrawBoard()
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

void Application::DrawCell(Vector2Int cellIndex, Color color)
{
    renderer->DrawRect(GetCellRect(cellIndex), color);
}

void Application::DrawPieces()
{
    for (const PieceData& piece : pieces)
    {
        DrawPiece(piece);
    }
}

void Application::DrawPiece(const PieceData& pieceData)
{
    int32_t pieceSize = piecesTexture->GetSize().x / 6;
    Vector2Int sourceOrigin = Vector2Int(static_cast<int32_t>(pieceData.type), static_cast<int32_t>(pieceData.color)) * pieceSize;
    Vector2Int sourceSize = { pieceSize, pieceSize };

    renderer->DrawTexture(*piecesTexture, Rect(sourceOrigin, sourceSize), GetCellRect(pieceData.index));
}

Rect Application::GetCellRect(Vector2Int cellIndex) const
{
    Vector2Int cellSize = Vector2Int::One() * GetCellSize();
    const Vector2Int cellPosition = GetBorderSize() + (cellIndex * GetCellSize());
    return Rect(cellPosition, cellSize);
}

int32_t Application::GetCellSize() const
{
    const int32_t windowSize = std::min(window->GetSize().x, window->GetSize().y);
    const int32_t cellSize = windowSize / 8;

    return cellSize;
}

int32_t Application::GetBoardSize() const
{
    return GetCellSize() * 8;
}

Vector2Int Application::GetBorderSize() const
{
    const Vector2Int windowSize = window->GetSize();
    const int32_t borderWidth = (windowSize.x - GetBoardSize()) / 2;
    const int32_t borderHeight = (windowSize.y - GetBoardSize()) / 2;

    return Vector2Int(borderWidth, borderHeight);
}