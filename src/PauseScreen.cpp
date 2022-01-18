#include "PauseScreen.hpp"

/*--------------------------------------------------------------------------------------------------------------*/

PauseScreen::PauseScreen() : escapePressed(false)
{

}

/*--------------------------------------------------------------------------------------------------------------*/

void PauseScreen::display(sf::RenderWindow &window, sf::Font font, sf::Text &pause, current_game_state &state)
{
    // Vérifie si la touche échap est appuyée
    if(this->escapePressed)
    {
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            this->escapePressed = false;
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->escapePressed = true;

        state.state = PLAY;
    }


    // Permet le rebondissement du menu pause
    if(pause.getPosition().x >= window.getSize().x - 40*5)
    {
        this->position_x = -5;
    }

    else if(pause.getPosition().x <= 0)
    {
        this->position_x = 5;
    }

    if(pause.getPosition().y >= window.getSize().y - 80)
    {
        this->position_y = -5;
    }

    else if(pause.getPosition().y <= 0)
    {
        this->position_y = 5;
    }

    pause.setPosition(pause.getPosition().x + this->position_x, pause.getPosition().y + this->position_y);
    window.draw(pause);
}

/*--------------------------------------------------------------------------------------------------------------*/