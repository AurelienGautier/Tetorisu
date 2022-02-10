#include "PauseScreen.hpp"

/*--------------------------------------------------------------------------------------------------------------*/

PauseScreen::PauseScreen(current_game_state &state) : escapePressed(true)
{
    pause.setString("PAUSE");
    pause.setFont(state.font);
    pause.setCharacterSize(80);
}

/*--------------------------------------------------------------------------------------------------------------*/

void PauseScreen::display(sf::RenderWindow &window, current_game_state &state)
{
    if(keyPressed(this->escapePressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
        state.state = PLAY;
    }

    // Modifie la position du texte PAUSE
    if(this->pause.getPosition().x >= window.getSize().x - 40*5)
    {
        this->position_x = -5;
    }

    else if(this->pause.getPosition().x <= 0)
    {
        this->position_x = 5;
    }

    if(this->pause.getPosition().y >= window.getSize().y - 80)
    {
        this->position_y = -5;
    }

    else if(this->pause.getPosition().y <= 0)
    {
        this->position_y = 5;
    }

    // Place le texte PAUSE au bon endroit
    this->pause.setPosition(this->pause.getPosition().x + this->position_x, this->pause.getPosition().y + this->position_y);
    window.draw(this->pause);
}

/*--------------------------------------------------------------------------------------------------------------*/