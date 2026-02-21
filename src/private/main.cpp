#include <Application.h>
#include <ChessBoardView.h>
#include <Renderer.h>
#include <Window.h>
#include <ChessBoard.h>

int main()
{
    Application application;
    ChessBoard board(application.GetInput());
    ChessBoardView view(board, application.GetInput());

    application.GetOnInitializeRender().RegisterCallback([&view](Window* window, Renderer* renderer) 
    { 
        view.InitializeRender(window, renderer); 
    });
    
    application.GetOnRender().RegisterCallback([&view]() 
    { 
        view.Render(); 
    });

    application.GetOnUpdate().RegisterCallback([&board]()
    {
        board.Update();
    });

    application.Initialize();
    application.Run();

    return 0;
}
