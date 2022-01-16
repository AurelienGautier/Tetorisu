#pragma once
#include "global.hpp"

class PauseScreen
{
    public:
        PauseScreen();
        void pause_menu(sf::RenderWindow &window, sf::Font font, sf::Text &pause, current_game_state &state);

    private:
        int position_x, position_y;
        bool escapePressed;
};