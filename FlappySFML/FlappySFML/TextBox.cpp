#include "TextBox.h"

/// <summary>
/// Initialize a TextBox with give font and its size
/// </summary>
/// <param name="font"></param>
/// <param name="characterSize"></param>
TextBox::TextBox(const sf::Font& font, unsigned int characterSize)
    : text("", font, 20), background(sf::Vector2f(200.f, 20 + 10.f))
{
    text.setFillColor(sf::Color::Black);
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(4.f);
    background.setOutlineColor(sf::Color::Black);
}

/// <summary>
/// Set manually position of the TextBox
/// </summary>
/// <param name="position"></param>
void TextBox::setPosition(const sf::Vector2f& position)
{
    text.setPosition(position + sf::Vector2f(5.f, 5.f));
    background.setPosition(position);
}

/// <summary>
/// Set the predefined text in the TextBox
/// </summary>
/// <param name="string"></param>
void TextBox::setString(const sf::String& string)
{
    text.setString(string);
}

/// <summary>
/// Get string from the TextBox
/// </summary>
/// <returns></returns>
std::string TextBox::getString()
{
    return text.getString();
}

/// <summary>
/// Handle user input
/// </summary>
/// <param name="event"></param>
void TextBox::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode == 8 && !text.getString().isEmpty())
        {
            //handle backspace
            text.setString(text.getString().substring(0, text.getString().getSize() - 1));
        }
        //only digits are allowed
        else if (event.text.unicode >= 48 && event.text.unicode <= 57)
        {
            //maximum length is 3
            if (text.getString().getSize() < 3)
            {
                text.setString(text.getString() + event.text.unicode);
            }
        }
    }
}

/// <summary>
/// Draws TextBox to the give RenderTarget
/// </summary>
/// <param name="target"></param>
/// <param name="states"></param>
void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(background, states);
    target.draw(text, states);
}

/// <summary>
/// Check if the given point is placed inside the TextBox
/// </summary>
/// <param name="point"></param>
/// <returns></returns>
bool TextBox::contains(const sf::Vector2f& point) const
{
    return background.getGlobalBounds().contains(point);
}

