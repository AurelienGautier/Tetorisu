#include "headers/Button.hpp"

Button::Button() 
{

}

/*--------------------------------------------------------------------------------------------------------------*/

Button::Button(int upEdge, int leftEdge)
{
    this->setPos(upEdge, leftEdge);
}

/*--------------------------------------------------------------------------------------------------------------*/

Button::Button(int leftEdge, int upEdge, std::string string, sf::Font font, int charSize)
{
    this->setPos(upEdge, leftEdge);
    this->setText(string, font, charSize);
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

bool Button::isClicked(sf::Vector2i mousePosition)
{
    if(mousePosition.x >= this->leftEdge && 
       mousePosition.x <= this->rightEdge && 
       mousePosition.y >= this->upEdge && 
       mousePosition.y <= this->downEdge)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return true;
        }
    }

    return false;
}

/*--------------------------------------------------------------------------------------------------------------*/

void Button::display(sf::RenderWindow &window)
{
    this->text.setPosition(this->leftEdge, this->upEdge);
    window.draw(this->text);
}

/*--------------------------------------------------------------------------------------------------------------*/
