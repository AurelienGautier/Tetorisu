#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "grid.hpp"
#include "global.hpp"

#define LEVEL_POSITION_X (window.getSize().x/2 - CASE_SIZE*5 - 5*40)
#define LEVEL_POSITION_Y SCORE_POSITION_Y

class Gameplay
{
    public:
        Gameplay(sf::Font font);
        void game_loop(sf::RenderWindow &window, sf::Font font, current_game_state &state, sf::Text &pause);
        void manage_rotation(current_game_state &state);
        void manage_left_and_right(current_game_state &state);
        void manage_tetromino_falling(current_game_state &state);
        void manage_instant_falling(current_game_state &state);
        void manage_quick_falling(current_game_state &state);
        void display_level(sf::RenderWindow &window, sf::Font &font);
        void reset();

    private:
        bool grid_initialized;
        bool DownPressed, Wpressed, UpPressed, spacePressed, escapePressed;
        int time, move_timer, level, scoreComparison;
        float speed;
        Grid grid;
        sf::Music music;
        bool music_launched, incrementLevel;
};