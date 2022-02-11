#include "GameOver.hpp"

GameOver::GameOver()
{

}

/*--------------------------------------------------------------------------------------------------------------*/

void GameOver::display(sf::RenderWindow &window, currentGameState &state)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    // Initialisation des boutons
    Button gameOver(GAMEOVER_X, GAMEOVER_Y, "GAME OVER", state.font, 80);
    Button retry(RETRY_X, RETRY_Y, "RETRY ?", state.font, 50);
    Button yes(YES_X, YES_Y, "YES", state.font, 50);
    Button no(NO_X, NO_Y, "NO", state.font, 50);

    // Affichage des boutons
    gameOver.display(window);
    retry.display(window);
    yes.display(window);
    no.display(window);

    // Clique des boutons
    if(yes.isClicked(mousePosition))
        state.state = PLAY;
    else if(no.isClicked(mousePosition))
        state.state = GAME_MENU;
}

/*--------------------------------------------------------------------------------------------------------------*/