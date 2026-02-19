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

Application::Application()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        return;
    }

    window = std::make_unique<Window>(WindowTitle, Vector2Int(700, 700));
    renderer = std::make_unique<Renderer>(window->CreateRenderer());
}

Application::~Application()
{
    SDL_Quit();
}

void Application::Run()
{
    renderer->SetClearColor(clearColor);

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
            const bool isDark = ((x + y) % 2) == 0;
            Color currentCellColor = isDark ? darkCellColor : lightCellColor;
            DrawCell(Vector2Int(x, y), currentCellColor);
        }
    }
}

void Application::DrawCell(Vector2Int cellIndex, Color color)
{
    Vector2Int cellSize = Vector2Int::One() * GetCellSize();
    const Vector2Int cellPosition = GetBorderSize() + (cellIndex * GetCellSize());

    renderer->DrawRect(cellPosition, cellSize, color);
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