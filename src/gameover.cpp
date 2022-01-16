#include "gameover.hpp"

GameOver::GameOver()
{

}

/*--------------------------------------------------------------------------------------------------------------*/

void GameOver::gameoverMenu(sf::RenderWindow &window, sf::Font &font, current_game_state &state, sf::View &view)
{
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

    displaying_text(window, "GAME OVER", font, 80, GAMEOVER_X, GAMEOVER_Y);
    displaying_text(window, "RETRY ?", font, 50, RETRY_X, RETRY_Y);

    displaying_text(window, "YES", font, 50, YES_X, YES_Y);
    this->gameover_manage_clic(mousePosition, YES_X, YES_X+3*25, YES_Y, YES_Y+50, PLAY, state);

    displaying_text(window, "NO", font, 50, NO_X, NO_Y);
    this->gameover_manage_clic(mousePosition, NO_X, NO_X+3*25, NO_Y, NO_Y+50, GAME_MENU, state);
}

/*--------------------------------------------------------------------------------------------------------------*/

void GameOver::gameover_manage_clic(sf::Vector2f mousePosition, int left_edge, int right_edge, int up_edge, int down_edge, int action, current_game_state &state)
{
    if(mousePosition.x > left_edge && mousePosition.x < right_edge && mousePosition.y > up_edge && mousePosition.y < down_edge)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            state.state = action;
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------*/