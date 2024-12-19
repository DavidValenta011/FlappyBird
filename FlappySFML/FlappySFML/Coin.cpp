#include "Coin.h"

Coin::Coin()
{
    for (const auto& path : {
        "res/textures/bird/4-2.png",
        "res/textures/bird/4-3.png",
        "res/textures/bird/4-2.png",
        "res/textures/bird/4-1.png",
        })
    {
        sf::Texture* frame = new sf::Texture();
        frame->loadFromFile(path);
        frames.push_back(frame);
    }
    texture = new sf::Texture();
    texture->loadFromFile("res/textures/coin.png");
    x = 100;
}

Coin::~Coin()
{
    for (const auto& ptr : frames)
    {
        delete ptr;
    }
}

sf::FloatRect Coin::getRect() const
{
    auto size = texture->getSize();
    return {
        100, y,
        (float)size.x, (float)size.y
    };
}

void Coin::draw(sf::RenderWindow* window)
{
    sf::Sprite coinSprite(*texture);
    coinSprite.setPosition(x, 100);
    window->draw(coinSprite);
}

void Coin::update(bool& gameRunning, bool& gameOvered, const float& deltaTime, int& gameSpeed, const Bird* bird, int& score)
{
    if (!gameRunning || gameOvered) return;

    x -= gameSpeed * deltaTime;
    auto birdRect = bird->getRect();

    /*if (birdRect.intersects(getUpperRect()) || birdRect.intersects(getLowerRect()))
    {
        gameOvered = true;
    }

    if (x + upperPipe->getSize().x < birdRect.left && !scored)
    {
        scored = true;
        score++;
        //gameSpeed += 15;
    }*/
}