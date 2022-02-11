#include "Gameplay.hpp"
#include <iostream>
/*--------------------------------------------------------------------------------------------------------------*/

Gameplay::Gameplay()
{
    this->reset();
    this->music.openFromFile("sounds/cityRuins.wav");
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::display(sf::RenderWindow &window, currentGameState &state)
{
    // Met le jeu en pause si la fenêtre n'est pas au premier plan
    if(!window.hasFocus())        
    {
        state.state = PAUSE;
    }

    if(!music_launched)
    {
        this->music.play();
        music_launched = true;
    }

    if(keyPressed(this->escapePressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
        state.state = PAUSE;
    }

    if(this->incrementLevel)
    {
        if(!(grid.get_score()-this->scoreComparison >= 1000))
        {
            this->incrementLevel = false;
        }
    }

    else if(grid.get_score()-this->scoreComparison >= 1000 && this->level<10)
    {
        level++;
        speed -= 1.5;
        scoreComparison += 1000;

        this->incrementLevel = true;
    }


    grid.display_grid(window);
    grid.display_score(window, state.font);
    grid.display_tetr_to_come(window);
    this->displayLevel(window, state.font);

    this->manageRotation(state);
    this->manageLeftAndRight(state);
    this->manageTetrominoFalling(state);
    this->manageInstantFalling(state);
    this->manageQuickFalling(state);
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::manageRotation(currentGameState &state)
{
    // Rotation gauche
    if(keyPressed(this->Wpressed, sf::Keyboard::isKeyPressed(state.controls[LEFT_ROTATION])))
    {
        grid.rotate('L');
    }

    // Rotation droite
    if(keyPressed(this->UpPressed, sf::Keyboard::isKeyPressed(state.controls[RIGHT_ROTATION])))
    {
        grid.rotate('R');
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::manageLeftAndRight(currentGameState &state)
{
    if(this->move_timer == 0)
    {
        if(sf::Keyboard::isKeyPressed(state.controls[MOVE_LEFT]))
        {
            this->move_timer = 1;
            grid.move_tetromino_left();
        }

        else if(sf::Keyboard::isKeyPressed(state.controls[MOVE_RIGHT]))
        {
            this->move_timer = 1;
            grid.move_tetromino_right();
        }
    }

    else
    {
        this->move_timer = (1 + this->move_timer) % 5;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::manageTetrominoFalling(currentGameState &state)
{
    if(this->time == 0)
    {
        this->time = 1;

        if(!grid.fall_tetromino())
        {
            grid.reset();
            this->reset();
            state.state = GAME_OVER;
        }
    }

    else
    {
        this->time = (1 + time) % (int)this->speed;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::manageInstantFalling(currentGameState &state)
{
    if(keyPressed(spacePressed, sf::Keyboard::isKeyPressed(state.controls[INSTANT_DESCENT])))
    {
        grid.go_down();
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::manageQuickFalling(currentGameState &state)
{
    if(this->DownPressed)
    {
        if(!sf::Keyboard::isKeyPressed(state.controls[QUICK_DESCENT]))
        {
            this->speed*=4;
            this->DownPressed = false;
        }
    } else if(sf::Keyboard::isKeyPressed(state.controls[QUICK_DESCENT]))
    {
        this->speed/=4;
        this->DownPressed = true;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::displayLevel(sf::RenderWindow &window, sf::Font font)
{
    sf::Text level("LEVEL : "+std::to_string(this->level), font, 50);
    level.setPosition(LEVEL_POSITION_X, LEVEL_POSITION_Y);
    window.draw(level);
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::reset()
{
    this->time = 0;
    this->move_timer = 0;
    this->speed = 18;
    this->level = 1;
    this->scoreComparison = 0;
    this->grid_initialized = false;
    this->music_launched = false;
    this->incrementLevel = false;
}

/*--------------------------------------------------------------------------------------------------------------*/