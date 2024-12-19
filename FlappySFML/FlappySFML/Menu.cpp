#include "Menu.h"

Menu::Menu()
{
    menuWindow = new sf::RenderWindow(sf::VideoMode(507, 508), "Welcome to the Flappy Penguin!");
    menuWindow->setPosition({ 100, 100 });

    menuBackground = new sf::Texture();
    menuBackground->loadFromFile("Assets/welcome.png");

    sf::Image* icon = new sf::Image();
    icon->loadFromFile("Assets/p1.png");
    menuWindow->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());
    delete icon;

    font = new sf::Font();
    font->loadFromFile("Assets/ComicSans.TTF");

    // gamespeed row
    textGameSpeed = new sf::Text("Game speed:", *font);
    textGameSpeed->setPosition(sf::Vector2f(10.f, 10.f));
    textGameSpeed->setFillColor(sf::Color::Black);

    textBoxGameSpeed = new TextBox(*font, 20);
    textBoxGameSpeed->setPosition(sf::Vector2f(textGameSpeed->getGlobalBounds().width + 20.f, 11.f));
    
    // obstacle frequency row
    textObstacleFrequency = new sf::Text("Obstacle frequency:", *font);
    textObstacleFrequency->setPosition(sf::Vector2f(10.f, 70.f));
    textObstacleFrequency->setFillColor(sf::Color::Black);

    textBoxObstacleFrequency = new TextBox(*font, 20);
    textBoxObstacleFrequency->setPosition(sf::Vector2f(textObstacleFrequency->getGlobalBounds().width + 20.f, 70.f));
    
    // use ceiling row
    textUseCeiling = new sf::Text("Use ceiling:", *font);
    textUseCeiling->setPosition(sf::Vector2f(10.f, 130.f));
    textUseCeiling->setFillColor(sf::Color::Black);

    checkBoxUseCeiling = new Checkbox();
    checkBoxUseCeiling->setPosition(sf::Vector2f(textUseCeiling->getGlobalBounds().width + 20.f, 110.f));
    
    // increasing speed row
    textIncreasingSpeed = new sf::Text("Increasing speed:", *font);
    textIncreasingSpeed->setPosition(sf::Vector2f(10.f, 190.f));
    textIncreasingSpeed->setFillColor(sf::Color::Black);

    checkBoxIncreasingSpeed = new Checkbox();
    checkBoxIncreasingSpeed->setPosition(sf::Vector2f(textIncreasingSpeed->getGlobalBounds().width + 20.f, 170.f));
    

    textTapToStart = new sf::Text("PRESS SPACE TO\nSTART THE GAME", *font);
    textTapToStart->setPosition(sf::Vector2f(100.f, 350.f));
    textTapToStart->setFillColor(sf::Color::Black);

    

    activeTextbox = nullptr;
    tappedToStart = false;
}

Menu::~Menu()
{
    delete menuWindow;
    delete menuBackground;
    delete font;
    delete textGameSpeed;
    delete textBoxGameSpeed;
    delete textObstacleFrequency;
    delete textBoxObstacleFrequency;
    delete textUseCeiling;
    delete checkBoxUseCeiling;
    delete textIncreasingSpeed;
    delete checkBoxIncreasingSpeed;
    delete textTapToStart;
    delete activeTextbox;
}

/// <summary>
/// Handle user input
/// </summary>
/// <param name="event"></param>
void Menu::handleEvent(sf::Event& event)
{
    while (menuWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            menuWindow->close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePosition = menuWindow->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            if (textBoxGameSpeed->contains(mousePosition))
            {
                activeTextbox = textBoxGameSpeed;
            }
            else if (textBoxObstacleFrequency->contains(mousePosition))
            {
                activeTextbox = textBoxObstacleFrequency;
            }
            else if (checkBoxUseCeiling->contains(mousePosition))
            {
                checkBoxUseCeiling->handleEvent(event);
            }
            else if (checkBoxIncreasingSpeed->contains(mousePosition))
            {
                checkBoxIncreasingSpeed->handleEvent(event);
            }
        }
        else if (event.type == sf::Event::TextEntered && event.text.unicode == 32)
        {
            tappedToStart = true;
        }

        if (activeTextbox != nullptr)
        {
            activeTextbox->handleEvent(event);
        }
    }
}

/// <summary>
/// Draw all components in the menu
/// </summary>
void Menu::draw()
{
    menuWindow->clear(sf::Color::White);
    menuWindow->draw(sf::Sprite(*menuBackground));
    textBoxGameSpeed->draw(*menuWindow);
    textBoxObstacleFrequency->draw(*menuWindow);
    checkBoxUseCeiling->draw(*menuWindow);
    checkBoxIncreasingSpeed->draw(*menuWindow);
    menuWindow->draw(*textGameSpeed);
    menuWindow->draw(*textObstacleFrequency);
    menuWindow->draw(*textUseCeiling);
    menuWindow->draw(*textIncreasingSpeed);
    menuWindow->draw(*textTapToStart);
    menuWindow->display();
}

/// <summary>
/// Run the main loop of the menu
/// </summary>
/// <param name="gameSpeed"></param>
/// <param name="pipeDistance"></param>
/// <param name="ceiling"></param>
/// <param name="increasingSpeed"></param>
/// <returns></returns>
int Menu::Run(int& gameSpeed, int& pipeDistance, bool& ceiling, bool& increasingSpeed)
{
    textBoxGameSpeed->setString(std::to_string(gameSpeed));
    textBoxObstacleFrequency->setString(std::to_string(pipeDistance));
    checkBoxUseCeiling->setChecked(ceiling);
    checkBoxIncreasingSpeed->setChecked(increasingSpeed);
    while (menuWindow->isOpen() && !tappedToStart)
    {
        sf::Event event;
        handleEvent(event);

        draw();
    }
    try
    {
        gameSpeed = std::stoi(textBoxGameSpeed->getString());
    }
    catch (...)
    {
        gameSpeed = 0;
    }
    try
    {
        pipeDistance = std::stoi(textBoxObstacleFrequency->getString());
    }
    catch (...)
    {
        pipeDistance = 0;
    }
    if (gameSpeed < 100)
    {
        gameSpeed = 100;
    }
    if (pipeDistance < 170)
    {
        pipeDistance = 170;
    }
    ceiling = checkBoxUseCeiling->isChecked();
    increasingSpeed = checkBoxIncreasingSpeed->isChecked();

    menuWindow->close();
    return tappedToStart ? EXIT_SUCCESS : EXIT_FAILURE;
}