#include "headers/Settings.hpp"
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

    // Initialisation des boutons uniquement affichables
    Button instantDescent(INSTANT_DESCENT_X, INSTANT_DESCENT_Y, "INSTANT DESCENT", state.font, 50);
    Button quickDescent(QUICK_DESCENT_X, QUICK_DESCENT_Y, "QUICK DESCENT", state.font, 50);
    Button leftRotation(LEFT_ROTATE_X, LEFT_ROTATE_Y, "LEFT ROTATION", state.font, 50);
    Button rightRotation(RIGHT_ROTATE_X, RIGHT_ROTATE_KEY_Y, "RIGHT ROTATION", state.font, 50);
    Button moveLeft(MOVE_LEFT_X, MOVE_LEFT_Y, "MOVE LEFT", state.font, 50);
    Button moveRight(MOVE_RIGHT_X, MOVE_RIGHT_Y, "MOVE RIGHT", state.font, 50);

    // Affichage des boutons uniquement affichables
    instantDescent.display(window);
    quickDescent.display(window);
    leftRotation.display(window);
    rightRotation.display(window);
    moveLeft.display(window);
    moveRight.display(window);

    // Initialisation des boutons cliquables
    Button back(BACK_BUTTON_X, BACK_BUTTON_Y, "BACK", state.font, 50);
    Button instantDescentKey(INSTANT_DESCENT_KEY_X, INSTANT_DESCENT_KEY_Y, keys[INSTANT_DESCENT], state.font, 50);
    Button quickDescentKey(QUICK_DESCENT_KEY_X, QUICK_DESCENT_KEY_Y, keys[QUICK_DESCENT], state.font, 50);
    Button leftRotationKey(LEFT_ROTATE_KEY_X, LEFT_ROTATE_KEY_Y, keys[LEFT_ROTATION], state.font, 50);
    Button rightRotationKey(RIGHT_ROTATE_KEY_X, RIGHT_ROTATE_KEY_Y, keys[RIGHT_ROTATION], state.font, 50);
    Button moveLeftKey(MOVE_LEFT_KEY_X, MOVE_LEFT_KEY_Y, keys[MOVE_LEFT], state.font, 50);
    Button moveRightKey(MOVE_RIGHT_KEY_X, MOVE_RIGHT_KEY_Y, keys[MOVE_RIGHT], state.font, 50);

    // Affichage des boutons cliquables
    back.display(window);
    instantDescentKey.display(window);
    quickDescentKey.display(window);
    leftRotationKey.display(window);
    rightRotationKey.display(window);
    moveLeftKey.display(window);
    moveRightKey.display(window);

    // Clique des boutons
    if(back.isClicked(mousePosition))
        state.state = GAME_MENU;
    else if(instantDescentKey.isClicked(mousePosition))
        state.settingsControls = INSTANT_DESCENT;
    else if(quickDescentKey.isClicked(mousePosition))
        state.settingsControls = QUICK_DESCENT;
    else if(leftRotationKey.isClicked(mousePosition))
        state.settingsControls = LEFT_ROTATION;
    else if(rightRotationKey.isClicked(mousePosition))
        state.settingsControls = RIGHT_ROTATION;
    else if(moveLeftKey.isClicked(mousePosition))
        state.settingsControls = MOVE_LEFT;
    else if(moveRightKey.isClicked(mousePosition))
        state.settingsControls = MOVE_RIGHT;
}

/*--------------------------------------------------------------------------------------------------------------*/