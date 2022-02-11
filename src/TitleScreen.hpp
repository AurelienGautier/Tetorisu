#pragma once
#include <SFML/Graphics.hpp>
#include "global.hpp"
#include "Button.hpp"

#define SPACE_BETWEEN 100

#define TITLE_POSITION_X window.getSize().x/3
#define TITLE_POSITION_Y window.getSize().y/4

#define PLAY_POSITION_X TITLE_POSITION_X
#define PLAY_POSITION_Y TITLE_POSITION_Y  + SPACE_BETWEEN + 80

#define SETTINGS_POSITION_X TITLE_POSITION_X
#define SETTINGS_POSITION_Y PLAY_POSITION_Y + SPACE_BETWEEN

#define LEAVE_POSITION_X TITLE_POSITION_X
#define LEAVE_POSITION_Y SETTINGS_POSITION_Y + SPACE_BETWEEN

class TitleScreen
{
    public:
        TitleScreen();
        void display(sf::RenderWindow &window, currentGameState &state);
        void titlescreen_manage_clic(sf::Vector2i mousePosition, int left_edge, int right_edge, int up_edge, int down_edge, int action, currentGameState &state);
        
    private:
        int buttonPoliceSize = 50;
        int titlePoliceSize = 80;
};