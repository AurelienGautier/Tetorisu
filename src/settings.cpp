#include "settings.hpp"

Settings::Settings(current_game_state &state)
{
    this->initKeys();
    this->initControls(state);
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

void Settings::initControls(current_game_state &state)
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

void Settings::changeControl(int control_to_change, int keyPressed, current_game_state &state)
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

void Settings::display_settings(sf::RenderWindow &window, sf::Font &font, current_game_state &state, sf::View &view)
{
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);

    // Affichage et utilisation du bouton de retour au menu
    displaying_text(window, "BACK", font, 50, BACK_BUTTON_X, BACK_BUTTON_Y);

    if(mousePosition.x > BACK_BUTTON_X && mousePosition.x < BACK_BUTTON_X + 100 && mousePosition.y > BACK_BUTTON_Y && mousePosition.y < BACK_BUTTON_Y + 50)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            state.state = GAME_MENU;
        }
    }

    // Réglage du contrôle de la descente instantannée du tetromino
    displaying_text(window, "INSTANT DESCENT", font, 50, INSTANT_DESCENT_X, INSTANT_DESCENT_Y);
    displaying_text(window, keys[INSTANT_DESCENT], font, 50, INSTANT_DESCENT_KEY_X, INSTANT_DESCENT_KEY_Y);
    this->settings_manage_clic(mousePosition, INSTANT_DESCENT_KEY_X, INSTANT_DESCENT_KEY_Y, INSTANT_DESCENT_Y+50, INSTANT_DESCENT, state);

    // Réglage du contrôle de la descente rapide du tetromino
    displaying_text(window, "QUICK DESCENT", font, 50, QUICK_DESCENT_X, QUICK_DESCENT_Y);
    displaying_text(window, keys[QUICK_DESCENT], font, 50, QUICK_DESCENT_KEY_X, QUICK_DESCENT_KEY_Y);
    this->settings_manage_clic(mousePosition, QUICK_DESCENT_KEY_X, QUICK_DESCENT_KEY_Y, QUICK_DESCENT_Y+50, QUICK_DESCENT, state);

    // Réglage du contrôle de la rotation gauche du tetromino
    displaying_text(window, "LEFT ROTATION", font, 50, LEFT_ROTATE_X, LEFT_ROTATE_Y);
    displaying_text(window, keys[LEFT_ROTATION], font, 50, LEFT_ROTATE_KEY_X, LEFT_ROTATE_KEY_Y);
    this->settings_manage_clic(mousePosition, LEFT_ROTATE_KEY_X, LEFT_ROTATE_KEY_Y, LEFT_ROTATE_Y+50, LEFT_ROTATION, state);

    // Réglage du contrôle de la rotation droite du tetromino
    displaying_text(window, "RIGHT ROTATION", font, 50, RIGHT_ROTATE_X, RIGHT_ROTATE_Y);
    displaying_text(window, keys[RIGHT_ROTATION], font, 50, RIGHT_ROTATE_KEY_X, RIGHT_ROTATE_KEY_Y);
    this->settings_manage_clic(mousePosition, RIGHT_ROTATE_KEY_X, RIGHT_ROTATE_KEY_Y, RIGHT_ROTATE_Y+50, RIGHT_ROTATION, state);

    // Réglage du contrôle du mouvement vers la gauche du tetromino
    displaying_text(window, "MOVE LEFT", font, 50, MOVE_LEFT_X, MOVE_LEFT_Y);
    displaying_text(window, keys[MOVE_LEFT], font, 50, MOVE_LEFT_KEY_X, MOVE_LEFT_KEY_Y);
    this->settings_manage_clic(mousePosition, MOVE_LEFT_KEY_X, MOVE_LEFT_KEY_Y, MOVE_LEFT_Y+50, MOVE_LEFT, state);

    // Réglage du contrôle du mouvement vers la droite du tetromino
    displaying_text(window, "MOVE RIGHT", font, 50, MOVE_RIGHT_X, MOVE_RIGHT_Y);
    displaying_text(window, keys[MOVE_RIGHT], font, 50, MOVE_RIGHT_KEY_X, MOVE_RIGHT_KEY_Y);
    this->settings_manage_clic(mousePosition, MOVE_RIGHT_KEY_X, MOVE_RIGHT_KEY_Y, MOVE_RIGHT_Y+50, MOVE_RIGHT, state); 
}

/*--------------------------------------------------------------------------------------------------------------*/

void Settings::settings_manage_clic(sf::Vector2f mousePosition, int left_edge, int up_edge, int down_edge, int action, current_game_state &state)
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