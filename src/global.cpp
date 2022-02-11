#include "global.hpp"
#include <iostream>

void displayingText(sf::RenderWindow &window, std::string textToDisplay, sf::Font &font, int size, int positionX, int positionY)
{
    sf::Text thingToDisplay(textToDisplay, font, size);
    thingToDisplay.setPosition(positionX, positionY);
    window.draw(thingToDisplay);
}

/*--------------------------------------------------------------------------------------------------------------*/

// Permet d'éviter les appuis maintenus
bool keyPressed(bool &keyPressed, const bool keyPressedSF)
{   
    // Merci Loudrasiel :)
    if(keyPressed)
    {
        if(!keyPressedSF)
        {
            keyPressed = false;
        }
    } 
    else if(keyPressedSF)
    {
        keyPressed = true;
        return true;
    }

    return false;
}

/*--------------------------------------------------------------------------------------------------------------*/