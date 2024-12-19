#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include <iostream>

#include "Bird.h"

#pragma once
class Pipe
{
private:
    float x;
    float y;
    bool scored;
    //sf::Texture* texture;

public:
    sf::Texture* upperPipe;
    sf::Texture* lowerPipe;
    Pipe(float xWindow);
    sf::FloatRect getUpperRect() const;
    sf::FloatRect getLowerRect() const;
    void draw(sf::RenderTarget* target) const;
    void update(bool& gameOvered, const float& deltaTime, int& gameSpeed, const Bird* bird, int& score, bool& increaseSpeed);
};