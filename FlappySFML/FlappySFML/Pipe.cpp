#include "Pipe.h"


Pipe::Pipe(float xWindow)
{
    upperPipe = new sf::Texture();
    lowerPipe = new sf::Texture();
    sf::Image pipeImage;
    pipeImage.loadFromFile("Assets/pipe.png");
    upperPipe->loadFromImage(pipeImage);
    pipeImage.flipVertically();
    lowerPipe->loadFromImage(pipeImage);

    x = (float)(xWindow + upperPipe->getSize().x);
    y = 100.0f + (float)(rand() % 5 - 3) * 50;
    scored = false;
}

/// <summary>
/// Get floatRect representation of the upper pipe
/// </summary>
/// <returns></returns>
sf::FloatRect Pipe::getUpperRect() const
{
    auto upperPipeSize = upperPipe->getSize();
    float upperRectX = x;
    float upperRectY = y + 340;
    float upperRectWidth = (float)upperPipeSize.x;
    float upperRectHeight = (float)upperPipeSize.y;

    return sf::FloatRect(upperRectX, upperRectY, upperRectWidth, upperRectHeight);
}

/// <summary>
/// Get floatRect representation of the lower pipe
/// </summary>
/// <returns></returns>
sf::FloatRect Pipe::getLowerRect() const
{
    auto upperPipeSize = upperPipe->getSize();
    float lowerRectX = x;
    float lowerRectY = y - 340;
    float lowerRectWidth = (float)upperPipeSize.x;
    float lowerRectHeight = (float)upperPipeSize.y;

    return sf::FloatRect(lowerRectX, lowerRectY, lowerRectWidth, lowerRectHeight);
}

/// <summary>
/// Draw both upper and lower pipe on the give target
/// </summary>
/// <param name="target"></param>
void Pipe::draw(sf::RenderTarget* target) const
{
    sf::Sprite upperSprite(*upperPipe);
    upperSprite.setPosition(x, y + 340);
    sf::Sprite lowerSprite(*lowerPipe);
    lowerSprite.setPosition(x, y - 340);

    target->draw(upperSprite);
    target->draw(lowerSprite);
}

/// <summary>
/// Update pipe positions according to the game state and the bird. 
/// It checks the collisions with the bird as well.
/// The game state fields are referenced, so we can
/// modify them here.
/// </summary>
/// <param name="gameOvered"></param>
/// <param name="deltaTime"></param>
/// <param name="gameSpeed"></param>
/// <param name="bird"></param>
/// <param name="score"></param>
/// <param name="increaseSpeed"></param>
void Pipe:: update(bool& gameOvered, const float& deltaTime, int& gameSpeed, const Bird* bird, int& score, bool& increaseSpeed)
{
    if (!gameOvered)
    {
        x -= gameSpeed * deltaTime;
        sf::FloatRect upperRect = getUpperRect();
        sf::FloatRect lowerRect = getLowerRect();
        sf::FloatRect birdRect = bird->getRect();

        if (birdRect.intersects(upperRect) || birdRect.intersects(lowerRect))
        {
            gameOvered = true;
        }

        if (!scored && birdRect.left > x + upperPipe->getSize().x)
        {
            scored = true;
            score++;
            if (increaseSpeed)
            {
                gameSpeed += 15;
            }
        }
    }
}
