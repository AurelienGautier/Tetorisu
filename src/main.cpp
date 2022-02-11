#include <SFML/Graphics.hpp>
#include "global.hpp"
#include "TitleScreen.hpp"
#include "Settings.hpp"
#include "Gameplay.hpp"
#include "PauseScreen.hpp"
#include "GameOver.hpp"

int main()
{
    // Déclaration de la structure contenant l'état du jeu
    currentGameState state;
    state.font.loadFromFile("fonts/BMgermar.TTF");

    // Initialisation de l'arrière-plan
    sf::Sprite background;
    sf::Texture textureBackground;
    textureBackground.loadFromFile("textures/backgrounds/background.jpg");
    background.setTexture(textureBackground);

    // Déclaration des objets composant le jeu
    TitleScreen titlescreen;
    Settings settings(state);
    Gameplay gameplay;
    PauseScreen pausescreen(state);
    GameOver gameover;

    // Création de la fenêtre et de la vue
    sf::RenderWindow window(sf::VideoMode(state.windowWidth, state.windowHeight), "Tetorisu");
    sf::View view(sf::Vector2f(window.getSize().x/2, window.getSize().y/2), sf::Vector2f(state.windowWidth, state.windowHeight));
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // Vide la fenêtre et affiche l'arrrière-plan
        window.clear();
        background.setPosition(0,0);
        window.draw(background);

        // Gestion des différents écrans
        switch(state.state)
        {
            case GAME_MENU:
                titlescreen.display(window, state);
                break;
            case SETTINGS:
                settings.display(window, state);
                break;
            case PLAY:
                gameplay.display(window, state);
                break;
            case PAUSE:
                pausescreen.display(window, state);
                break;
            case GAME_OVER:
                gameover.display(window, state);
                break;
            case LEAVE:
                window.close();
                break;
        }

        // Gestion des événements
        sf::Event event;
        while(window.pollEvent(event)) 
        {
            if(event.type == sf::Event::Closed) 
            {
                window.close();
            }

            // Changement des contrôles dans le menu settings
            if(event.type == sf::Event::KeyPressed)
            {
                switch(state.settingsControls)
                {
                    case INSTANT_DESCENT:
                        settings.changeControl(INSTANT_DESCENT, event.key.code, state);
                        break;
                    case QUICK_DESCENT:
                        settings.changeControl(QUICK_DESCENT, event.key.code, state);
                        break;
                    case LEFT_ROTATION:
                        settings.changeControl(LEFT_ROTATION, event.key.code, state);
                        break;
                    case RIGHT_ROTATION:
                        settings.changeControl(RIGHT_ROTATION, event.key.code, state);
                        break;
                    case MOVE_LEFT:
                        settings.changeControl(MOVE_LEFT, event.key.code, state);
                        break;
                    case MOVE_RIGHT:
                        settings.changeControl(MOVE_RIGHT, event.key.code, state);
                        break;
                }
                state.settingsControls = -1;
            }

            // Redimensionnement de la fenêtre
            if(event.type == sf::Event::Resized)
            {
                float aspectRatio = float(window.getSize().x / float(window.getSize().y));
                view.setSize(1080*aspectRatio, 1080);
            }
        }

        // Affichage de la fenêtre et de la vue
        window.setView(view);
        window.display();
    }
    
    return 0;
}