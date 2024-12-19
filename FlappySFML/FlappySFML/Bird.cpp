#include "Bird.h"

Bird::Bird()
{
    for (const auto& path : {
        "Assets/p2.png",
        "Assets/p3.png",
        "Assets/p2.png",
        "Assets/p1.png",
        })
    {
        sf::Texture* frame = new sf::Texture();
        frame->loadFromFile(path);
        frames.push_back(frame);
    }
    texture = frames[0];

    y = 400;                                             
    velocity = 0;                                             
}                                                        
                                                         
Bird::~Bird()                                            
{                                                        
    for (auto it = frames.begin(); it != frames.end(); ++it)
    {
        delete* it;
        *it = nullptr;
    }
}

/// <summary>
/// Get bird shape as sf::FloatRect
/// </summary>
/// <returns></returns>
sf::FloatRect Bird::getRect() const
{
    auto textureSize = texture->getSize();
    float rectX = 50.0f;
    float rectY = y;
    float rectWidth = (float)textureSize.x;
    float rectHeight = (float)textureSize.y;

    return sf::FloatRect(rectX, rectY, rectWidth, rectHeight);
}
                  
/// <summary>
/// Flap with the bird
/// </summary>
void Bird::flap()                                        
{        
    velocity = -420;
}             

/// <summary>
/// Set manually vertical coordinate of the bird
/// </summary>
/// <param name="y"></param>
void Bird::setY(float y)
{
    this->y = y;
}
                  
/// <summary>
/// Draws the bird on the give RenderTarget
/// </summary>
/// <param name="window"></param>
void Bird::draw(sf::RenderTarget* target)
{                                                        
    sf::Sprite birdSprite(*texture);                     
    birdSprite.setRotation(8 * (velocity / 400));             
    birdSprite.setPosition(50, y);
    target->draw(birdSprite);
}

/// <summary>
/// Updates bird according to the given game state. 
/// The game state fields are passed as reference, so they
/// can be modified here
/// </summary>
/// <param name="gameOvered"></param>
/// <param name="deltaTime"></param>
/// <param name="backgroundTexture"></param>
/// <param name="ceiling"></param>
void Bird::update(bool& gameOvered, const float& deltaTime, sf::Texture* backgroundTexture, bool& ceiling)
{
    currentFrame += deltaTime * 4;
    if (currentFrame > frames.size())
    {
        currentFrame -= frames.size();
    }
    texture = frames[(int)currentFrame];
    
    if (!gameOvered)
    {
        velocity += deltaTime * 1200;
        y += velocity * deltaTime;

        if ((y < 0 && ceiling) || y + texture->getSize().y > backgroundTexture->getSize().y)
        {
            gameOvered = true;
        }

        if (y + texture->getSize().y > backgroundTexture->getSize().y)
        {
            y = (float)backgroundTexture->getSize().y - texture->getSize().y;
            velocity = 0;
        }
    }
    else if (y + texture->getSize().y < backgroundTexture->getSize().y)
    {
        velocity += deltaTime * 1200;
        y += velocity * deltaTime;
    }
}