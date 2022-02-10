#include "GameOver.hpp"

GameOver::GameOver()
{

}

/*--------------------------------------------------------------------------------------------------------------*/

void GameOver::display(sf::RenderWindow &window, current_game_state &state)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    displaying_text(window, "GAME OVER", state.font, 80, GAMEOVER_X, GAMEOVER_Y);
    displaying_text(window, "RETRY ?", state.font, 50, RETRY_X, RETRY_Y);

    displaying_text(window, "YES", state.font, 50, YES_X, YES_Y);
    this->gameover_manage_clic(mousePosition, YES_X, YES_X+3*25, YES_Y, YES_Y+50, PLAY, state);

    displaying_text(window, "NO", state.font, 50, NO_X, NO_Y);
    this->gameover_manage_clic(mousePosition, NO_X, NO_X+3*25, NO_Y, NO_Y+50, GAME_MENU, state);
}

/*--------------------------------------------------------------------------------------------------------------*/

void GameOver::gameover_manage_clic(sf::Vector2i mousePosition, int left_edge, int right_edge, int up_edge, int down_edge, int action, current_game_state &state)
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