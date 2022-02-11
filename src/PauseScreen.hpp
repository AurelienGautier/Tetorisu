#pragma once
#include "global.hpp"

class PauseScreen
{
    public:
        PauseScreen(currentGameState &state);
        void display(sf::RenderWindow &window, currentGameState &state);

    private:
        int position_x, position_y;
        bool escapePressed;
        sf::Text pause;
};