#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include <iostream>


#pragma once
class Ground
{
private:
    float offset;
	sf::Texture* texture;
    float y;

public:
    Ground(unsigned int y);
    void draw(sf::RenderTarget* target);
    sf::FloatRect getRect();
    void update(const float& deltaTime, const int& gameSpeed);
};
