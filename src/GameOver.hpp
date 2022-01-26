#pragma once
#include "global.hpp"

#define GAMEOVER_X window.getSize().x/3
#define GAMEOVER_Y window.getSize().y/4

#define RETRY_X GAMEOVER_X
#define RETRY_Y GAMEOVER_Y+200

#define YES_X RETRY_X
#define YES_Y RETRY_Y+100
#define NO_X YES_X + 200
#define NO_Y YES_Y

class GameOver
{
    public:
        GameOver();
        void display(sf::RenderWindow &window, sf::Font &font, current_game_state &state);
        void gameover_manage_clic(sf::Vector2i mousePosition, int left_edge, int right_edge, int up_edge, int down_edge, int action, current_game_state &state);

    private:

};