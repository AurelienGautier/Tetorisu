#pragma once
#include <SFML/Graphics.hpp>

constexpr unsigned char CASE_SIZE = 35;
constexpr unsigned char NEXT = 20;

constexpr unsigned char GRID_WIDTH = 20;
constexpr unsigned char GRID_HEIGHT = 10;

constexpr short SCREEN_WIDTH = GRID_HEIGHT * CASE_SIZE * 2;
constexpr short SCREEN_HEIGHT = GRID_WIDTH * CASE_SIZE;

constexpr short TETR_TO_COME_X = (SCREEN_WIDTH / 2) + CASE_SIZE;
constexpr short TETR_TO_COME_Y = CASE_SIZE * 5;

constexpr short HOLDING_PLACE_X = TETR_TO_COME_X;
constexpr short HOLDING_PLACE_Y = CASE_SIZE * 2;

constexpr unsigned char NB_KEYS = 7;

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
    MOVE_RIGHT,
    HOLD
};

struct currentGameState {
    int state = GAME_MENU;
    int settingsControls = -1;
    sf::Keyboard::Key controls[NB_KEYS];
    int windowWidth;
    int windowHeight;
    sf::Font font;
};
typedef struct currentGameState currentGameState;

void displayingText(sf::RenderWindow &window, std::string textToDisplay, sf::Font &font, int size, int positionX, int positionY);
void manage_clic(int left_edge, int up_edge, int down_edge, int action, currentGameState &state);
bool keyPressed(bool &keyPressed, const bool keyPressedSF);

std::vector<std::vector<char>> copy_matrix(std::vector<std::vector<char>> matrix);
std::vector<std::vector<char>> rotate_matrix(std::vector<std::vector<char>> matrix, char side);
void display_matrix(sf::RenderWindow& window, 
                    std::vector<std::vector<char>>& matrix, 
                    short pos_x, 
                    short pos_y, 
                    sf::RectangleShape& cell, 
                    sf::Color color,
                    unsigned char case_to_display);

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
