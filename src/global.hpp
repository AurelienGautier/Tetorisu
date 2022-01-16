#pragma once
#include <SFML/Graphics.hpp>

enum 
{
    GAME_MENU = 0,
    SETTINGS,
    LEAVE,
    PLAY,
    PAUSE,
    GAME_OVER
};

enum
{
    INSTANT_DESCENT = 0,
    QUICK_DESCENT,
    LEFT_ROTATION,
    RIGHT_ROTATION,
    MOVE_LEFT,
    MOVE_RIGHT
};

struct current_game_state {
    int state = GAME_MENU;
    int settingsControls = -1;
    sf::Keyboard::Key controls[6];
};
typedef struct current_game_state current_game_state;


void displaying_text(sf::RenderWindow &window, std::string text_to_display, sf::Font &font, int size, int position_x, int position_y);
void manage_clic(int left_edge, int up_edge, int down_edge, int action, current_game_state &state);
void keypressed(bool keyPressed);


// Affichage pour le gameplay
#define CASE_SIZE 35

#define GRID_CASE_POSITION_X (window.getSize().x/2 - CASE_SIZE*5) + CASE_SIZE*j
#define GRID_CASE_POSITION_Y (window.getSize().y/2 - CASE_SIZE*10) + CASE_SIZE*i

#define SCORE_POSITION_X (window.getSize().x/2) + CASE_SIZE*5
#define SCORE_POSITION_Y (window.getSize().y/2 - CASE_SIZE*10)

#define TETR_TO_COME_X SCORE_POSITION_X + 32
#define TETR_TO_COME_Y SCORE_POSITION_Y + 50

constexpr int PAUSE_X = 800;
constexpr int PAUSE_Y = 400;
