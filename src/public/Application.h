#pragma once
#include <string>
#include <unordered_set>
#include <Color.h>
#include <SDL.h>
#include <memory>
#include <Vector2Int.h>
#include <Renderer.h>
#include <Window.h>

class Application
{
private:
    const std::string WindowTitle = "Idea Chess";

    std::unordered_set<SDL_EventType> currentInput;
    Color lightCellColor = Colors::White;
    Color darkCellColor = Colors::Black;

    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;

public:
    Application();
    ~Application();

    void Run();
    void PollInput();
    void DrawBoard();
    void DrawCell(Vector2Int cellIndex, Color color);

    int32_t GetCellSize() const;
    int32_t GetBorderSize() const;
    int32_t GetBoardSize() const;
};