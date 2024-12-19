#include <SFML/Graphics.hpp>

#include "CheckBox.h"
#include "TextBox.h"
#include "Game.h"

#pragma once
class Menu
{
private:
    sf::RenderWindow* menuWindow;
    sf::Texture* menuBackground;
    sf::Font* font;
    sf::Text* textGameSpeed;
    TextBox* textBoxGameSpeed;
    sf::Text* textObstacleFrequency;
    TextBox* textBoxObstacleFrequency;
    sf::Text* textUseCeiling;
    Checkbox* checkBoxUseCeiling;
    sf::Text* textIncreasingSpeed;
    Checkbox* checkBoxIncreasingSpeed;
    sf::Text* textTapToStart;
    TextBox* activeTextbox;
    bool tappedToStart;
    void draw();
    void handleEvent(sf::Event& event);

public:
    Menu();
    ~Menu();
    int Run(int& gameSpeed, int& pipeDistance, bool& ceiling, bool& increasingSpeed);
};