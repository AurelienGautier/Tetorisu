#include "TitleScreen.hpp"
#include <iostream>

TitleScreen::TitleScreen()
{

}

/*--------------------------------------------------------------------------------------------------------------*/

void TitleScreen::display(sf::RenderWindow &window, current_game_state &state)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    displaying_text(window, "TETORISU", state.font, 80, TITLE_POSITION_X, TITLE_POSITION_Y);

    displaying_text(window, "PLAY", state.font, 50, PLAY_POSITION_X, PLAY_POSITION_Y);
    this->titlescreen_manage_clic(mousePosition, PLAY_POSITION_X, PLAY_POSITION_X+100, PLAY_POSITION_Y, PLAY_POSITION_Y+50, PLAY, state);

    displaying_text(window, "SETTINGS", state.font, 50, SETTINGS_POSITION_X, SETTINGS_POSITION_Y);
    this->titlescreen_manage_clic(mousePosition, SETTINGS_POSITION_X, SETTINGS_POSITION_X+200, SETTINGS_POSITION_Y, SETTINGS_POSITION_Y+50, SETTINGS, state);

    displaying_text(window, "LEAVE", state.font, 50, LEAVE_POSITION_X, LEAVE_POSITION_Y);
    this->titlescreen_manage_clic(mousePosition, LEAVE_POSITION_X, LEAVE_POSITION_X+125, LEAVE_POSITION_Y, LEAVE_POSITION_Y+50, LEAVE, state);
}

/*--------------------------------------------------------------------------------------------------------------*/

void TitleScreen::titlescreen_manage_clic(sf::Vector2i mousePosition, int left_edge, int right_edge, int up_edge, int down_edge, int action, current_game_state &state)
{
    if(mousePosition.x > left_edge && mousePosition.x < right_edge && mousePosition.y > up_edge && mousePosition.y < down_edge)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            state.state = action;
        }
    }
}