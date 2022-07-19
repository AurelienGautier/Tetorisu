#include "headers/GameOver.hpp"

GameOver::GameOver()
{

}

/*--------------------------------------------------------------------------------------------------------------*/

void GameOver::display(sf::RenderWindow &window, currentGameState &state)
{
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Initialisation des boutons
    Button gameOver(GAMEOVER_X, GAMEOVER_Y, "GAME OVER", state.font, 80, NOT_CLICKABLE);
    Button retry(RETRY_X, RETRY_Y, "RETRY ?", state.font, 50, NOT_CLICKABLE);
    Button yes(YES_X, YES_Y, "YES", state.font, 50, CLICKABLE);
    Button no(NO_X, NO_Y, "NO", state.font, 50, CLICKABLE);

    // Affichage des boutons
    gameOver.display(window, mousePosition);
    retry.display(window, mousePosition);
    yes.display(window, mousePosition);
    no.display(window, mousePosition);

    // Clique des boutons
    if(yes.isClicked(mousePosition, state.isLBMpressed))
        state.state = PLAY;
    else if(no.isClicked(mousePosition, state.isLBMpressed))
        state.state = GAME_MENU;
}

/*--------------------------------------------------------------------------------------------------------------*/