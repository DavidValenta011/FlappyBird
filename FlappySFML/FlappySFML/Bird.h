#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#pragma once
class Bird
{
private:
    sf::Texture* texture;
    float y;
    float velocity;
    float currentFrame{};
    std::vector<sf::Texture*> frames;

public:
    Bird();                                            
    ~Bird();
    sf::FloatRect getRect() const;
    void flap();
    void setY(float y);
    void draw(sf::RenderTarget* target);
    void update(bool& gameOvered, const float& deltaTime, sf::Texture* backgroundTexture, bool& ceiling);
};