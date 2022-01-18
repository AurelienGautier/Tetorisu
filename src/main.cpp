#include <SFML/Graphics.hpp>
#include "global.hpp"
#include "TitleScreen.hpp"
#include "Settings.hpp"
#include "Gameplay.hpp"
#include "PauseScreen.hpp"
#include "GameOver.hpp"
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

    current_game_state state;

    TitleScreen titlescreen;
    Settings settings(state);
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
        if(state.state == GAME_MENU)
        {
            titlescreen.display(window, font, state, view);
        }

        // Ecran des paramètres
        else if(state.state == SETTINGS)
        {
            settings.display(window, font, state, view);
        }

        // Ecran de jeu
        else if(state.state == PLAY)
        {
            gameplay.display(window, font, state, pause);
        }

        // Ecran de pause
        else if(state.state == PAUSE)
        {
            pausescreen.display(window, font, pause, state);
        }

        // Ecran de game over
        else if(state.state == GAME_OVER)
        {
            gameover.display(window, font, state, view);
        }

        // Fermer le jeu
        else if(state.state == LEAVE)
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

            switch(state.settingsControls)
            {
                case INSTANT_DESCENT:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(INSTANT_DESCENT, event.key.code, state);
                        state.settingsControls = -1;
                    }
                    break;
                case QUICK_DESCENT:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(QUICK_DESCENT, event.key.code, state);
                        state.settingsControls = -1;
                    }
                    break;
                case LEFT_ROTATION:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(LEFT_ROTATION, event.key.code, state);
                        state.settingsControls = -1;
                    }
                    break;
                case RIGHT_ROTATION:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(RIGHT_ROTATION, event.key.code, state);
                        state.settingsControls = -1;
                    }
                    break;
                case MOVE_LEFT:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(MOVE_LEFT, event.key.code, state);
                        state.settingsControls = -1;
                    }
                    break;
                case MOVE_RIGHT:
                    if(event.type == sf::Event::KeyPressed)
                    {
                        settings.changeControl(MOVE_RIGHT, event.key.code, state);
                        state.settingsControls = -1;
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