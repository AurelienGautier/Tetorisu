#include "headers/Button.hpp"
#include <iostream> // temporaire

/*--------------------------------------------------------------------------------------------------------------*/

Button::Button(int leftEdge, int upEdge, std::string string, sf::Font font, int charSize, bool clickable)
{
    this->setPos(upEdge, leftEdge);
    this->setText(string, font, charSize);
    this->clickable = clickable;
}

/*--------------------------------------------------------------------------------------------------------------*/

void Button::setPos(int upEdge, int leftEdge)
{
    this->upEdge = upEdge;
    this->leftEdge = leftEdge;
}

/*--------------------------------------------------------------------------------------------------------------*/

void Button::setText(std::string string, sf::Font font, int charSize)
{
    this->string = string;
    this->font = font;
    this->charSize = charSize;

    this->text.setString(this->string);
    this->text.setFont(this->font);
    this->text.setCharacterSize(this->charSize);

    this->downEdge = this->upEdge + charSize;
    this->rightEdge = this->leftEdge + string.size()*(charSize/2);
}

/*--------------------------------------------------------------------------------------------------------------*/

bool Button::isCursorOn(sf::Vector2f mousePosition)
{
    if (mousePosition.x >= this->leftEdge &&
        mousePosition.x <= this->rightEdge &&
        mousePosition.y >= this->upEdge &&
        mousePosition.y <= this->downEdge)
    {
        return true;
    }

    return false;
}

/*--------------------------------------------------------------------------------------------------------------*/

//keyPressed(bool &keyPressed, const bool keyPressedSF)
bool Button::isClicked(sf::Vector2f mousePosition, bool &isLMBpressed)
{
    if(isCursorOn(mousePosition) && keyPressed(isLMBpressed, sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        return true;
    }

    return false;
}

/*--------------------------------------------------------------------------------------------------------------*/

void Button::display(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    this->text.setFillColor(sf::Color::White);

    if (this->isCursorOn(mousePosition) && this->clickable)
    {
        sf::RectangleShape rectangle(sf::Vector2f(this->rightEdge - this->leftEdge, this->downEdge - this->upEdge));
        rectangle.setPosition(this->leftEdge, this->upEdge);

        this->text.setFillColor(sf::Color::Black);

        window.draw(rectangle);
    }

    this->text.setPosition(this->leftEdge, this->upEdge);
    window.draw(this->text);
}

/*--------------------------------------------------------------------------------------------------------------*/

void Button::operator=(Button button)
{
    this->setPos(button.get_upEdge(), button.get_leftEdge());
    this->setText(button.get_string(), button.get_font(), button.get_charSize());
}

/*--------------------------------------------------------------------------------------------------------------*/