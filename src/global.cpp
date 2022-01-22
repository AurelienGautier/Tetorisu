#include "global.hpp"
#include <iostream>

void displaying_text(sf::RenderWindow &window, std::string text_to_display, sf::Font &font, int size, int position_x, int position_y)
{
    sf::Text thing_to_display(text_to_display, font, size);
    thing_to_display.setPosition(position_x, position_y);
    window.draw(thing_to_display);
}

/*--------------------------------------------------------------------------------------------------------------*/

// Permet d'éviter les appuis maintenus
bool keyPressed(bool &keyPressed, const bool keyPressedSF)
{   
    if(keyPressed)
    {
        if(!keyPressedSF)
        {
            keyPressed = false;
        }
    } else if(keyPressedSF)
    {
        keyPressed = true;
        return true;
    }

    return false;
}

/*--------------------------------------------------------------------------------------------------------------*/