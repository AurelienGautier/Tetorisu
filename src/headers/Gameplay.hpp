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
        Gameplay();
        void display(sf::RenderWindow &window, currentGameState &state);
        void manageRotation(currentGameState &state);
        void manageLeftAndRight(currentGameState &state);
        void manageTetrominoFalling(currentGameState &state);
        void manageInstantFalling(currentGameState &state);
        void manageQuickFalling(currentGameState &state);
        void displayLevel(sf::RenderWindow &window, sf::Font font);
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