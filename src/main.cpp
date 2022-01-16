#include <SFML/Graphics.hpp>
#include "titleScreen.hpp"
#include "settings.hpp"
#include "gameplay.hpp"
#include "pause.hpp"
#include "global.hpp"
#include "gameover.hpp"
#include <iostream>

int main()
{
    sf::Sprite background;
    sf::Texture textureBackground;
    
    textureBackground.loadFromFile("textures/backgrounds/background.jpg");
    background.setTexture(textureBackground);

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tetorisu", sf::Style::None);
    window.setFramerateLimit(60);

    sf::View view(sf::Vector2f(window.getSize().x/2, window.getSize().y/2), sf::Vector2f(1920, 1080));

    sf::Font font;
    font.loadFromFile("fonts/BMgermar.TTF");

    current_game_state current_game_state;

    TitleScreen titlescreen;
    Settings settings(current_game_state);
    Gameplay gameplay(font);
    PauseScreen pausescreen;
    GameOver gameover;

    sf::Text pause("PAUSE", font, 80);

    while (window.isOpen())
    {
        // vide la fenêtre et affiche l'image de fond
        window.clear();
        background.setPosition(0,0);
        window.draw(background);

        // Ecran titre
        if(current_game_state.state == GAME_MENU)
        {
            titlescreen.display_element(window, font, current_game_state, view);
        }

        // Ecran des paramètres
        else if(current_game_state.state == SETTINGS)
        {
            settings.display_settings(window, font, current_game_state, view);
        }

        // Ecran de jeu
        else if(current_game_state.state == PLAY)
        {
            gameplay.game_loop(window, font, current_game_state, pause);
        }

        // Ecran de pause
        else if(current_game_state.state == PAUSE)
        {
            pausescreen.pause_menu(window, font, pause, current_game_state);
        }

        // Ecran de game over
        else if(current_game_state.state == GAME_OVER)
        {
            gameover.gameoverMenu(window, font, current_game_state, view);
        }

        // Fermer le jeu
        else if(current_game_state.state == LEAVE)
        {
            window.close();
        }

        // Gestion des événements
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed) 
            {
                window.close();
            }

            switch(current_game_state.settingsControls)
            {
                case INSTANT_DESCENT:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(INSTANT_DESCENT, event.key.code, current_game_state);
                        current_game_state.settingsControls = -1;
                    }
                    break;
                case QUICK_DESCENT:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(QUICK_DESCENT, event.key.code, current_game_state);
                        current_game_state.settingsControls = -1;
                    }
                    break;
                case LEFT_ROTATION:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(LEFT_ROTATION, event.key.code, current_game_state);
                        current_game_state.settingsControls = -1;
                    }
                    break;
                case RIGHT_ROTATION:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(RIGHT_ROTATION, event.key.code, current_game_state);
                        current_game_state.settingsControls = -1;
                    }
                    break;
                case MOVE_LEFT:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(MOVE_LEFT, event.key.code, current_game_state);
                        current_game_state.settingsControls = -1;
                    }
                    break;
                case MOVE_RIGHT:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(MOVE_RIGHT, event.key.code, current_game_state);
                        current_game_state.settingsControls = -1;
                    }
                    break;
            }

            if(event.type == sf::Event::Resized)
            {
                float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
                view.setSize(1920*aspectRatio, 1080);
            }
        }

        // Affichache la fenêtre et ses éléments
        
        window.setView(view);
        window.display();
    }
    
    return 0;
}