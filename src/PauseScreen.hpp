#pragma once
#include "global.hpp"

class PauseScreen
{
    public:
        PauseScreen(current_game_state &state);
        void display(sf::RenderWindow &window, current_game_state &state);

    private:
        int position_x, position_y;
        bool escapePressed;
        sf::Text pause;
};