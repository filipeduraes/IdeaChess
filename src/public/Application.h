#pragma once

#include <string>
#include <memory>
#include <Renderer.h>
#include <Window.h>
#include <Event.h>
#include <Input.h>
#include <cstdint>

class Application
{
private:
    const double FIXED_UPDATE_MILLISECONDS = 2;
    const std::string WindowTitle = "Idea Chess";

    Event<Window*, Renderer*> onInitializeRenderer;

    Event<> onUpdate;
    Event<> onRender;

    Input input;

    std::unique_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;

public:
    ~Application();

    void Initialize();
    void Run();
    void PollInput();

    IEvent<Window*, Renderer*>& GetOnInitializeRender()
    {
        return onInitializeRenderer;
    }

    IEvent<>& GetOnUpdate()
    {
        return onUpdate;
    }

    IEvent<>& GetOnRender()
    {
        return onRender;
    }

    const Input& GetInput()
    {
        return input;
    }
};