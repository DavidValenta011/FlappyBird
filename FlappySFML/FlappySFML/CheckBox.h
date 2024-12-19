#include <SFML/Graphics.hpp>

#pragma once
class Checkbox
{
private:
    sf::Sprite uncheckedSprite;
    sf::Sprite checkedSprite;
    bool checked = false;
public:
    Checkbox();
    void draw(sf::RenderTarget& target);
    bool isChecked();
    void setPosition(sf::Vector2f position);
    void setChecked(bool checked);
    void handleEvent(const sf::Event& event);
    bool contains(const sf::Vector2f& point) const;
};
