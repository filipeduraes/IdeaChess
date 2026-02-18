#include <Application.h>

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
    while (true)
    {
        PollInput();

        if (currentInput.contains(SDL_EventType::SDL_QUIT))
        {
            break;
        }

        renderer->SetClearColor(Colors::Black);
        renderer->Clear();

        DrawBoard();

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
        currentInput.insert(static_cast<SDL_EventType>(event.type));
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
    const Vector2Int cellPosition = (Vector2Int::One() * (GetBorderSize() / 2)) + (cellIndex * GetCellSize());

    renderer->DrawRect(cellPosition, cellSize, color);
}

int32_t Application::GetCellSize() const
{
    const int32_t windowSize = window->GetSize().x;
    const int32_t cellSize = windowSize / 8;

    return cellSize;
}

int32_t Application::GetBorderSize() const
{
    const int32_t windowSize = window->GetSize().x;
    const int32_t border = windowSize - GetCellSize() * 8;

    return border;
}

int32_t Application::GetBoardSize() const
{
    return GetCellSize() * 8;
}