#include "Settings.hpp"
#include <iostream>

Settings::Settings(currentGameState &state)
{
    this->initKeys();
    this->initControls(state);

    std::ifstream resolutionFile("savedDatas/resolution.txt");

    if(resolutionFile.is_open())
    {
        resolutionFile >> state.windowWidth;
        resolutionFile >> state.windowHeight;
    } 

    else 
    {
        std::cout << "Fichier des paramètres de l'écran inaccessible." << std::endl;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Settings::initKeys()
{
    std::ifstream keyFile("savedDatas/Keys.txt");
    std::string key;
    int key_value;

    if(keyFile.is_open())
    {
        // Assignation des touches à leurs noms et inversement
        while(keyFile >> key >> key_value)
        {
            this->inputKeys[key] = (sf::Keyboard::Key)key_value;
            this->keysInputs[key_value] = key;
        }

        keyFile.close();
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Settings::initControls(currentGameState &state)
{
    std::ifstream controlsFile("savedDatas/controls.txt");
    int action;
    std::string key;

    if(controlsFile.is_open())
    {
        while(controlsFile >> action >> key)
        {
            state.controls[action] = this->inputKeys[key];
            this->keys[action] = key;
        }

        controlsFile.close();
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Settings::changeControl(int control_to_change, int keyPressed, currentGameState &state)
{
    std::ofstream controlsFile("savedDatas/controls.txt");
    int i=0;

    while(controlsFile.is_open() && i<=5)
    {
        if(i == control_to_change)
        {
            controlsFile << i << " " << this->keysInputs[keyPressed] << std::endl;
        }

        else
        {
            controlsFile << i << " " << this->keysInputs[state.controls[i]] << std::endl;
        }

        i++;
    }

    controlsFile.close();

    this->initControls(state);
}

/*--------------------------------------------------------------------------------------------------------------*/

void Settings::display(sf::RenderWindow &window, currentGameState &state)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    // Affichage et utilisation du bouton de retour au menu
    displayingText(window, "BACK", state.font, 50, BACK_BUTTON_X, BACK_BUTTON_Y);

    if(mousePosition.x > BACK_BUTTON_X && mousePosition.x < BACK_BUTTON_X + 100 && mousePosition.y > BACK_BUTTON_Y && mousePosition.y < BACK_BUTTON_Y + 50)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            state.state = GAME_MENU;
        }
    }

    // Réglage du contrôle de la descente instantannée du tetromino
    displayingText(window, "INSTANT DESCENT", state.font, 50, INSTANT_DESCENT_X, INSTANT_DESCENT_Y);
    displayingText(window, keys[INSTANT_DESCENT], state.font, 50, INSTANT_DESCENT_KEY_X, INSTANT_DESCENT_KEY_Y);
    this->settings_manage_clic(mousePosition, INSTANT_DESCENT_KEY_X, INSTANT_DESCENT_KEY_Y, INSTANT_DESCENT_Y+50, INSTANT_DESCENT, state);

    // Réglage du contrôle de la descente rapide du tetromino
    displayingText(window, "QUICK DESCENT", state.font, 50, QUICK_DESCENT_X, QUICK_DESCENT_Y);
    displayingText(window, keys[QUICK_DESCENT], state.font, 50, QUICK_DESCENT_KEY_X, QUICK_DESCENT_KEY_Y);
    this->settings_manage_clic(mousePosition, QUICK_DESCENT_KEY_X, QUICK_DESCENT_KEY_Y, QUICK_DESCENT_Y+50, QUICK_DESCENT, state);

    // Réglage du contrôle de la rotation gauche du tetromino
    displayingText(window, "LEFT ROTATION", state.font, 50, LEFT_ROTATE_X, LEFT_ROTATE_Y);
    displayingText(window, keys[LEFT_ROTATION], state.font, 50, LEFT_ROTATE_KEY_X, LEFT_ROTATE_KEY_Y);
    this->settings_manage_clic(mousePosition, LEFT_ROTATE_KEY_X, LEFT_ROTATE_KEY_Y, LEFT_ROTATE_Y+50, LEFT_ROTATION, state);

    // Réglage du contrôle de la rotation droite du tetromino
    displayingText(window, "RIGHT ROTATION", state.font, 50, RIGHT_ROTATE_X, RIGHT_ROTATE_Y);
    displayingText(window, keys[RIGHT_ROTATION], state.font, 50, RIGHT_ROTATE_KEY_X, RIGHT_ROTATE_KEY_Y);
    this->settings_manage_clic(mousePosition, RIGHT_ROTATE_KEY_X, RIGHT_ROTATE_KEY_Y, RIGHT_ROTATE_Y+50, RIGHT_ROTATION, state);

    // Réglage du contrôle du mouvement vers la gauche du tetromino
    displayingText(window, "MOVE LEFT", state.font, 50, MOVE_LEFT_X, MOVE_LEFT_Y);
    displayingText(window, keys[MOVE_LEFT], state.font, 50, MOVE_LEFT_KEY_X, MOVE_LEFT_KEY_Y);
    this->settings_manage_clic(mousePosition, MOVE_LEFT_KEY_X, MOVE_LEFT_KEY_Y, MOVE_LEFT_Y+50, MOVE_LEFT, state);

    // Réglage du contrôle du mouvement vers la droite du tetromino
    displayingText(window, "MOVE RIGHT", state.font, 50, MOVE_RIGHT_X, MOVE_RIGHT_Y);
    displayingText(window, keys[MOVE_RIGHT], state.font, 50, MOVE_RIGHT_KEY_X, MOVE_RIGHT_KEY_Y);
    this->settings_manage_clic(mousePosition, MOVE_RIGHT_KEY_X, MOVE_RIGHT_KEY_Y, MOVE_RIGHT_Y+50, MOVE_RIGHT, state); 
}

/*--------------------------------------------------------------------------------------------------------------*/

void Settings::settings_manage_clic(sf::Vector2i mousePosition, int left_edge, int up_edge, int down_edge, int action, currentGameState &state)
{
    if(mousePosition.x > left_edge && mousePosition.y > up_edge && mousePosition.y < down_edge)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            state.settingsControls = action;
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void resizeWindow(sf::RenderWindow &window, sf::View view)
{
    float aspectRatio = float(window.getSize().x / float(window.getSize().y));
}

/*--------------------------------------------------------------------------------------------------------------*/