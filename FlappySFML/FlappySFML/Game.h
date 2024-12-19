#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include <iostream>


#include "Pipe.h"
#include "Bird.h"
#include "Ground.h"


#pragma once
class Game
{
private:
    int score;
    int maxScore;
    bool gameOvered;
    float delta;
    int gameSpeed;
    int pipeDistance;
    bool ceiling;
    bool increaseSpeed;
    sf::RenderWindow* window;
    sf::Texture* backgroundTexture;
    Bird* bird;
    Ground* ground;
    sf::Texture* upperPipe;
    sf::Texture* lowerPipe;
    std::vector<Pipe*> pipes;
    sf::Clock* pipeGeneratingClock;
    sf::Font* font;
    void setup();
    void update();
    void handleEvent(sf::Event& event);
    void draw();

public:
    Game();
    ~Game();
    int Run(int gameSpeed, int pipeDistance, bool ceiling, bool increasingSpeed);
};