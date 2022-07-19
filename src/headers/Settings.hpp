#pragma once

#include "global.hpp"
#include <fstream>
#include "Button.hpp"
#include <array>

enum
{
    KEYS,
    SCREEN_RESOLUTION,
    SETTINGS_MENU
};

constexpr int SPACE_BETWEEN_SETTINGS_X = 550;
constexpr int SPACE_BETWEEN_SETTINGS_Y = 100;

constexpr int BACK_BUTTON_X = 50;
constexpr int BACK_BUTTON_Y = 30;

constexpr int INSTANT_DESCENT_X = 250;
constexpr int INSTANT_DESCENT_Y = 30;
constexpr int INSTANT_DESCENT_KEY_X = INSTANT_DESCENT_X + SPACE_BETWEEN_SETTINGS_X;
constexpr int INSTANT_DESCENT_KEY_Y = INSTANT_DESCENT_Y;
constexpr int CHANGE_INSTANT_DESCENT_X = 1250;
constexpr int CHANGE_INSTANT_DESCENT_Y = INSTANT_DESCENT_Y;

constexpr int QUICK_DESCENT_X = INSTANT_DESCENT_X;
constexpr int QUICK_DESCENT_Y = INSTANT_DESCENT_Y + SPACE_BETWEEN_SETTINGS_Y;
constexpr int QUICK_DESCENT_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int QUICK_DESCENT_KEY_Y = QUICK_DESCENT_Y;
constexpr int CHANGE_QUICK_DESCENT_X = CHANGE_INSTANT_DESCENT_X;
constexpr int CHANGE_QUICK_DESCENT_Y = QUICK_DESCENT_Y;

constexpr int LEFT_ROTATE_X = INSTANT_DESCENT_X;
constexpr int LEFT_ROTATE_Y = QUICK_DESCENT_Y + SPACE_BETWEEN_SETTINGS_Y;
constexpr int LEFT_ROTATE_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int LEFT_ROTATE_KEY_Y = LEFT_ROTATE_Y;
constexpr int CHANGE_LEFT_ROTATE_X = CHANGE_INSTANT_DESCENT_X;
constexpr int CHANGE_LEFT_ROTATE_Y = LEFT_ROTATE_Y;

constexpr int RIGHT_ROTATE_X = INSTANT_DESCENT_X;
constexpr int RIGHT_ROTATE_Y = LEFT_ROTATE_Y + SPACE_BETWEEN_SETTINGS_Y;
constexpr int RIGHT_ROTATE_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int RIGHT_ROTATE_KEY_Y = RIGHT_ROTATE_Y;
constexpr int CHANGE_RIGHT_ROTATE_X = CHANGE_INSTANT_DESCENT_X;
constexpr int CHANGE_RIGHT_ROTATE_Y = RIGHT_ROTATE_Y;

constexpr int MOVE_LEFT_X = INSTANT_DESCENT_X;
constexpr int MOVE_LEFT_Y = RIGHT_ROTATE_Y + SPACE_BETWEEN_SETTINGS_Y;
constexpr int MOVE_LEFT_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int MOVE_LEFT_KEY_Y = MOVE_LEFT_Y;
constexpr int CHANGE_MOVE_LEFT_X = CHANGE_INSTANT_DESCENT_X;
constexpr int CHANGE_MOVE_LEFT_Y = MOVE_LEFT_Y;

constexpr int MOVE_RIGHT_X = INSTANT_DESCENT_X;
constexpr int MOVE_RIGHT_Y = MOVE_LEFT_Y + SPACE_BETWEEN_SETTINGS_Y;
constexpr int MOVE_RIGHT_KEY_X = INSTANT_DESCENT_KEY_X;
constexpr int MOVE_RIGHT_KEY_Y = MOVE_RIGHT_Y;
constexpr int CHANGE_MOVE_RIGHT_X = CHANGE_INSTANT_DESCENT_X;
constexpr int CHANGE_MOVE_RIGHT_Y = MOVE_RIGHT_Y;

class Settings
{
private:
    void displayMenuSettings(sf::RenderWindow& window, currentGameState& state);
    void displayKeysSettings(sf::RenderWindow& window, currentGameState& state);
    void displayResolutionSettings(sf::RenderWindow& window, currentGameState& state);
    std::map<std::string, sf::Keyboard::Key> inputKeys; // la touche à partir du nom
    std::map<int, std::string> keysInputs;              // le nom à partir de la touche
    std::string keys[NB_KEYS];
    char concerned_setting;

public:
    Settings(currentGameState& state);
    void initKeys();
    void initControls(currentGameState& state);
    void changeControl(int control_to_change, int keyPressed, currentGameState& state);
    void display(sf::RenderWindow& window, sf::View& view, currentGameState& state);
    void settings_manage_clic(sf::Vector2i mousePosition, int left_edge, int up_edge, int down_edge, int action, currentGameState& state);
    void resizeWindow(sf::RenderWindow& window, sf::View view);
};