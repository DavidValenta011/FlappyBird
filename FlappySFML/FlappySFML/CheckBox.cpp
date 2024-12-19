#include "CheckBox.h"

Checkbox::Checkbox()
{
    sf::Texture* uncheckedTexture = new sf::Texture();
    uncheckedTexture->loadFromFile("Assets/checkboxOff.png");
    uncheckedSprite.setTexture(*uncheckedTexture);
    sf::Texture* checkedTexture = new sf::Texture();
    checkedTexture->loadFromFile("Assets/checkboxOn.png");
    checkedSprite.setTexture(*checkedTexture);

}

/// <summary>
/// Draw Checkbox on the given render target
/// </summary>
/// <param name="target"></param>
void Checkbox::draw(sf::RenderTarget& target)
{
    // render correct structure with respect to state of the checkbox
    if (checked)
    {
        target.draw(checkedSprite);
    }
    else
    {
        target.draw(uncheckedSprite);
    }
}

/// <summary>
/// Return state of the checkbox
/// </summary>
/// <returns></returns>
bool Checkbox::isChecked()
{
    return checked;
}

/// <summary>
/// Set position of the checkbox manually
/// </summary>
/// <param name="position"></param>
void Checkbox::setPosition(sf::Vector2f position)
{
    uncheckedSprite.setPosition(position);
    checkedSprite.setPosition(position);
}

/// <summary>
/// Select state of the checkbox
/// </summary>
/// <param name="checked"></param>
void Checkbox::setChecked(bool checked)
{
    this->checked = checked;
}

/// <summary>
/// Handle user input
/// </summary>
/// <param name="event"></param>
void Checkbox::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        checked = !checked;
    }
}

/// <summary>
/// Check if the given point is placed inside the checkbox
/// </summary>
/// <param name="point"></param>
/// <returns></returns>
bool Checkbox::contains(const sf::Vector2f& point) const
{
    return (checked ? checkedSprite : uncheckedSprite).getGlobalBounds().contains(point);
}
