#include "global.hpp"

void displaying_text(sf::RenderWindow &window, std::string text_to_display, sf::Font &font, int size, int position_x, int position_y)
{
    sf::Text thing_to_display(text_to_display, font, size);
    thing_to_display.setPosition(position_x, position_y);
    window.draw(thing_to_display);
}

/*--------------------------------------------------------------------------------------------------------------*/

void manage_clic(sf::RenderWindow &window, int left_edge, int up_edge, int down_edge, int action, current_game_state &state)
{
    
}

/*--------------------------------------------------------------------------------------------------------------*/

void keypressed(bool keyPressed)
{
    
}

/*--------------------------------------------------------------------------------------------------------------*/