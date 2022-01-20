#include "global.hpp"
#include <iostream>

void displaying_text(sf::RenderWindow &window, std::string text_to_display, sf::Font &font, int size, int position_x, int position_y)
{
    sf::Text thing_to_display(text_to_display, font, size);
    thing_to_display.setPosition(position_x, position_y);
    window.draw(thing_to_display);
}

/*--------------------------------------------------------------------------------------------------------------*/

bool keyPressed(bool &keyPressed, const bool keyPressedSF)
{
    std::cout << keyPressed << std::endl;
    std::cout << std::endl;
    if(!keyPressed && keyPressedSF)
    {
        keyPressed = true;
    }
    
    if(keyPressed)
    {
        if(!keyPressedSF)
        {
            keyPressed = false;
        }
    } else if(keyPressedSF)
    {
        keyPressed = true;
    }

    if(!keyPressed && keyPressedSF)
    {
        std::cout << keyPressed << std::endl;
        return true;
    }

    return false;
}

/*--------------------------------------------------------------------------------------------------------------*/