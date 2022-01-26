#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Grid.hpp"
#include "global.hpp"

#define LEVEL_POSITION_X (window.getSize().x/2 - CASE_SIZE*5 - 5*40)
#define LEVEL_POSITION_Y SCORE_POSITION_Y

class Gameplay
{
    public:
        Gameplay(sf::Font font);
        void display(sf::RenderWindow &window, sf::Font font, current_game_state &state, sf::Text &pause);
        void manageRotation(current_game_state &state);
        void manageLeftAndRight(current_game_state &state);
        void manageTetrominoFalling(current_game_state &state);
        void manageInstantFalling(current_game_state &state);
        void manageQuickFalling(current_game_state &state);
        void displayLevel(sf::RenderWindow &window, sf::Font &font);
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