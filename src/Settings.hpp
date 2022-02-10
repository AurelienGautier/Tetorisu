#pragma once

#include "global.hpp"
#include <fstream>

constexpr int SPACE_BETWEEN_SETTINGS = 100;

constexpr int BACK_BUTTON_X = 50;
constexpr int BACK_BUTTON_Y = 30;

constexpr int INSTANT_DESCENT_X = 250;
constexpr int INSTANT_DESCENT_Y = 30;
constexpr int INSTANT_DESCENT_KEY_X = 800;
constexpr int INSTANT_DESCENT_KEY_Y = INSTANT_DESCENT_Y;

constexpr int QUICK_DESCENT_X = INSTANT_DESCENT_X;
constexpr int QUICK_DESCENT_Y = INSTANT_DESCENT_Y + SPACE_BETWEEN_SETTINGS;
constexpr int QUICK_DESCENT_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int QUICK_DESCENT_KEY_Y = QUICK_DESCENT_Y;

constexpr int LEFT_ROTATE_X = INSTANT_DESCENT_X;
constexpr int LEFT_ROTATE_Y = QUICK_DESCENT_Y + SPACE_BETWEEN_SETTINGS;
constexpr int LEFT_ROTATE_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int LEFT_ROTATE_KEY_Y = LEFT_ROTATE_Y;

constexpr int RIGHT_ROTATE_X = INSTANT_DESCENT_X;
constexpr int RIGHT_ROTATE_Y = LEFT_ROTATE_Y + SPACE_BETWEEN_SETTINGS;
constexpr int RIGHT_ROTATE_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int RIGHT_ROTATE_KEY_Y = RIGHT_ROTATE_Y;

constexpr int MOVE_LEFT_X = INSTANT_DESCENT_X;
constexpr int MOVE_LEFT_Y = RIGHT_ROTATE_Y + SPACE_BETWEEN_SETTINGS;
constexpr int MOVE_LEFT_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int MOVE_LEFT_KEY_Y = MOVE_LEFT_Y;

constexpr int MOVE_RIGHT_X = INSTANT_DESCENT_X;
constexpr int MOVE_RIGHT_Y = MOVE_LEFT_Y + SPACE_BETWEEN_SETTINGS;
constexpr int MOVE_RIGHT_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int MOVE_RIGHT_KEY_Y = MOVE_RIGHT_Y;

class Settings
{
    public:
        Settings(current_game_state &state);
        void initKeys();
        void initControls(current_game_state &state);
        void changeControl(int control_to_change, int keyPressed, current_game_state &state);
        void display(sf::RenderWindow &window, current_game_state &state);
        void settings_manage_clic(sf::Vector2i mousePosition, int left_edge, int up_edge, int down_edge, int action, current_game_state &state);
        void resizeWindow(sf::RenderWindow &window, sf::View view);

    private:
        std::map<std::string, sf::Keyboard::Key> inputKeys; // la touche à partir du nom
        std::map<int, std::string> keysInputs;              // le nom à partir de la touche
        std::string keys[6];
};