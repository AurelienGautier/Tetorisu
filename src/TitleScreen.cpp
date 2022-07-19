#include "headers/TitleScreen.hpp"

TitleScreen::TitleScreen()
{
    
}

/*--------------------------------------------------------------------------------------------------------------*/

void TitleScreen::display(sf::RenderWindow &window, currentGameState &state)
{
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Initialisation des boutons
    Button title(TITLE_POSITION_X, TITLE_POSITION_Y, "TETORISU", state.font, this->titlePoliceSize, NOT_CLICKABLE);
    Button play(PLAY_POSITION_X, PLAY_POSITION_Y, "PLAY", state.font, this->buttonPoliceSize, CLICKABLE);
    Button settings(SETTINGS_POSITION_X, SETTINGS_POSITION_Y, "SETTINGS", state.font, this->buttonPoliceSize, CLICKABLE);
    Button leave(LEAVE_POSITION_X, LEAVE_POSITION_Y, "LEAVE", state.font, this->buttonPoliceSize, CLICKABLE);

    // Affichage des boutons
    title.display(window, mousePosition);
    play.display(window, mousePosition);
    settings.display(window, mousePosition);
    leave.display(window, mousePosition);

    // Click sur les boutons
    if(play.isClicked(mousePosition, state.isLBMpressed))
        state.state = PLAY;
    else if(settings.isClicked(mousePosition, state.isLBMpressed))
        state.state = SETTINGS;
    else if(leave.isClicked(mousePosition, state.isLBMpressed))
        state.state = LEAVE;
}

/*--------------------------------------------------------------------------------------------------------------*/