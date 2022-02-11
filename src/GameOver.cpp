#include "GameOver.hpp"

GameOver::GameOver()
{

}

/*--------------------------------------------------------------------------------------------------------------*/

void GameOver::display(sf::RenderWindow &window, currentGameState &state)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    displayingText(window, "GAME OVER", state.font, 80, GAMEOVER_X, GAMEOVER_Y);
    displayingText(window, "RETRY ?", state.font, 50, RETRY_X, RETRY_Y);

    displayingText(window, "YES", state.font, 50, YES_X, YES_Y);
    this->gameover_manage_clic(mousePosition, YES_X, YES_X+3*25, YES_Y, YES_Y+50, PLAY, state);

    displayingText(window, "NO", state.font, 50, NO_X, NO_Y);
    this->gameover_manage_clic(mousePosition, NO_X, NO_X+3*25, NO_Y, NO_Y+50, GAME_MENU, state);
}

/*--------------------------------------------------------------------------------------------------------------*/

void GameOver::gameover_manage_clic(sf::Vector2i mousePosition, int left_edge, int right_edge, int up_edge, int down_edge, int action, currentGameState &state)
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