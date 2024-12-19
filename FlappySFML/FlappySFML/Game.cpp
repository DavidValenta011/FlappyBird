#include "Game.h"

/// <summary>
/// Setup game window
/// </summary>
void Game::setup()
{
    srand((unsigned int)time(nullptr));
    pipeGeneratingClock = new sf::Clock;

    font = new sf::Font();
    font->loadFromFile("Assets/ComicSans.TTF");

    window = new sf::RenderWindow(sf::VideoMode(500, 700), "Flappy Penguin!");
    window->setPosition({ 100, 100 });

    sf::Image* icon = new sf::Image();
    icon->loadFromFile("Assets/p1.png");
    window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());

    bird = new Bird();

    backgroundTexture = new sf::Texture();
    backgroundTexture->loadFromFile("Assets/mff.png");

    ground = new Ground(backgroundTexture->getSize().y);

    upperPipe = new sf::Texture();
    lowerPipe = new sf::Texture();

    sf::Image pipeImage;
    pipeImage.loadFromFile("Assets/pipe.png");
    upperPipe->loadFromImage(pipeImage);
    pipeImage.flipVertically();
    lowerPipe->loadFromImage(pipeImage);


    gameSpeed = 100;
    pipeDistance = 170;
    ceiling = false;
    increaseSpeed = false;

    gameOvered = false;
}

/// <summary>
/// update game state
/// </summary>
void Game::update()
{
    bird->update(gameOvered, delta, backgroundTexture, ceiling);
    for (const auto& pipe : pipes)
    {
        pipe->update(gameOvered, delta, gameSpeed, bird, score, increaseSpeed);
    }
    if (!gameOvered)
    {
        if (pipeGeneratingClock->getElapsedTime().asSeconds() > static_cast<float>(pipeDistance) / gameSpeed)
        {
            pipeGeneratingClock->restart();
            pipes.push_back(new Pipe(static_cast<float>(window->getSize().x)));

            if (pipes.size() > 4)
            {
                delete pipes[0];
                pipes.erase(pipes.begin());
            }
        }
    }
}

/// <summary>
/// Handle user input
/// </summary>
/// <param name="event"></param>
void Game::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::Closed)
    {
        window->close();
    }
    if (event.type == sf::Event::MouseButtonPressed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space))
    {
        if (gameOvered)
        {
            gameOvered = false;
            pipes.clear();
            if (score > maxScore)
            {
                maxScore = score;
            }
            score = 0;
            bird->setY(100.f);
        }
        if (gameOvered)
        {
            gameOvered = false;
            pipeGeneratingClock->restart();
            pipes.push_back(new Pipe(static_cast<float>(window->getSize().x)));
        }
        if (!gameOvered)
        {
            bird->flap();
        }
    }
}

/// <summary>
/// Draw all components on itself
/// </summary>
void Game::draw()
{
    window->clear();
    window->draw(sf::Sprite(*backgroundTexture));

    for (const auto& pipe : pipes)
    {
        pipe->draw(window);
    }

    if (!gameOvered)
    {
        ground->update(delta, gameSpeed);
    }
    ground->draw(window);

    sf::RectangleShape lowerRectangle({
        (float)window->getSize().x,
        (float)window->getSize().y - backgroundTexture->getSize().y - ground->getRect().height
        });
    lowerRectangle.setPosition(0, (float)backgroundTexture->getSize().y + ground->getRect().height);
    lowerRectangle.setFillColor({ 245, 228, 138 });
    window->draw(lowerRectangle);


    bird->draw(window);

    //sf::Text scoreText("Score: " + std::to_string(score) + ", Record: " + std::to_string(maxScore), *font);
    sf::Text scoreText("abvvdvd: " + std::to_string(score) + ", Record: " + std::to_string(maxScore), *font);
    scoreText.setPosition(window->getSize().x / 2 - scoreText.getLocalBounds().width / 2, 5);
    scoreText.setFillColor(sf::Color::Cyan);
    window->draw(scoreText);
}


Game::Game()
{
    setup();
}

Game::~Game()
{
    delete window;
    delete bird;
    delete backgroundTexture;
    delete pipeGeneratingClock;
    delete font;
}

/// <summary>
/// Run the game loop
/// </summary>
/// <param name="gameSpeed"></param>
/// <param name="pipeDistance"></param>
/// <param name="ceiling"></param>
/// <param name="increasingSpeed"></param>
/// <returns></returns>
int Game::Run(int gameSpeed, int pipeDistance, bool ceiling, bool increasingSpeed)
{
    this->gameSpeed = gameSpeed;
    this->pipeDistance = pipeDistance;
    this->ceiling = ceiling;
    this->increaseSpeed = increasingSpeed;

    sf::Clock deltaClock;

    while (window->isOpen())
    {
        sf::Event event{};

        while (window->pollEvent(event))
        {
            handleEvent(event);
        }

        delta = deltaClock.getElapsedTime().asMicroseconds() / 1000.0f / 1000.0f;
        deltaClock.restart();

        update();
        draw();

        window->display();
    }

    return EXIT_SUCCESS;
}
