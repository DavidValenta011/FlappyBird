#include <SFML/Graphics.hpp>

#include "Bird.h"

#pragma once

class Coin
{
private:
    sf::Texture* texture;
    float x;
    float y;
    float currentFrame{};
    std::vector<sf::Texture*> frames;

public:
    Coin();
    ~Coin();
    sf::FloatRect getRect() const;
    void draw(sf::RenderWindow* window);
    void update(bool& gameRunning, bool& gameOvered, const float& deltaTime, int& gameSpeed, const Bird* bird, int& score);
};
