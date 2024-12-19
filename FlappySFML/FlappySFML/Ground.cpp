#include "Ground.h"


Ground::Ground(unsigned int y) : offset(0), texture(new sf::Texture()), y(y)
{
    texture->loadFromFile("Assets/ground.png");
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void Ground::draw(sf::RenderTarget* target)
{
    sf::Sprite groundSprite(*texture);
    groundSprite.setPosition(offset, y);
    target->draw(groundSprite);
}


/// <summary>
/// Get floatRect representing the ground
/// </summary>
/// <returns></returns>
sf::FloatRect Ground::getRect()
{
    sf::FloatRect rect;
    rect.left = offset;
    rect.top = y;
    rect.width = static_cast<float>(texture->getSize().x);
    rect.height = static_cast<float>(texture->getSize().y);
    return rect;
}

/// <summary>
/// Update the ground position
/// </summary>
/// <param name="deltaTime">CHange of time</param>
/// <param name="gameSpeed">Given speed</param>
void Ground::update(const float& deltaTime, const int& gameSpeed)
{
    offset -= deltaTime * gameSpeed;
    if (offset <= -24)
    {
        offset += 24;
    }
}