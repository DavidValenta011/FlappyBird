#include "Menu.h"
#include "Game.h"


constexpr int gameSpeed = 300;
constexpr int pipeDistance = 370;


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    int gameSpeedResult = gameSpeed;
    int pipeDistanceResult = pipeDistance;
    bool ceilingResult = false;
    bool increasingSpeedResult = false;


    Menu* menu = new Menu();
    if (menu->Run(gameSpeedResult, pipeDistanceResult, ceilingResult, increasingSpeedResult) == EXIT_SUCCESS)
    {
        Game* game = new Game();
        game->Run(gameSpeedResult, pipeDistanceResult, ceilingResult, increasingSpeedResult);
    }

    return EXIT_SUCCESS;
}