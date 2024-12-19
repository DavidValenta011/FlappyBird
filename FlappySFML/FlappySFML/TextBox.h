#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>


#pragma once
class TextBox
{
private:
    sf::Text text;
    sf::RectangleShape background;
public:
    TextBox(const sf::Font& font, unsigned int characterSize);
    void setPosition(const sf::Vector2f& position);
    void setString(const sf::String& string);
    std::string getString();
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
    bool contains(const sf::Vector2f& point) const;
};
