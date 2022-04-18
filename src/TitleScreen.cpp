#include "headers/TitleScreen.hpp"

TitleScreen::TitleScreen()
{
    
}

/*--------------------------------------------------------------------------------------------------------------*/

void TitleScreen::display(sf::RenderWindow &window, currentGameState &state)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    // Initialisation des boutons
    Button title(TITLE_POSITION_X, TITLE_POSITION_Y, "TETORISU", state.font, this->titlePoliceSize);
    Button play(PLAY_POSITION_X, PLAY_POSITION_Y, "PLAY", state.font, this->buttonPoliceSize);
    Button settings(SETTINGS_POSITION_X, SETTINGS_POSITION_Y, "SETTINGS", state.font, this->buttonPoliceSize);
    Button leave(LEAVE_POSITION_X, LEAVE_POSITION_Y, "LEAVE", state.font, this->buttonPoliceSize);

    // Affichage des boutons
    title.display(window);
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