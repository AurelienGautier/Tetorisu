#include "TitleScreen.hpp"
#include <iostream> // temporaire

TitleScreen::TitleScreen(currentGameState &state)
{
    
}

/*--------------------------------------------------------------------------------------------------------------*/

void TitleScreen::display(sf::RenderWindow &window, currentGameState &state)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    displayingText(window, "TETORISU", state.font, 80, TITLE_POSITION_X, TITLE_POSITION_Y);

    // Initialisation des boutons
    Button play(PLAY_POSITION_Y, PLAY_POSITION_X, "PLAY", state.font, this->buttonPoliceSize);
    Button settings(SETTINGS_POSITION_Y, SETTINGS_POSITION_X, "SETTINGS", state.font, this->buttonPoliceSize);
    Button leave(LEAVE_POSITION_Y, LEAVE_POSITION_X, "LEAVE", state.font, this->buttonPoliceSize);

    // Affichage des boutons
    play.display(window);
    settings.display(window);
    leave.display(window);

    // Click sur les boutons
    if(play.isClicked(mousePosition))
        state.state = PLAY;
    else if(settings.isClicked(mousePosition))
        state.state = SETTINGS;
    else if(leave.isClicked(mousePosition))
        state.state = LEAVE;
}

/*--------------------------------------------------------------------------------------------------------------*/