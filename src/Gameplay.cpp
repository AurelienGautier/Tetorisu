#include "Gameplay.hpp"
#include <iostream>
/*--------------------------------------------------------------------------------------------------------------*/

Gameplay::Gameplay(sf::Font font)
{
    this->reset();
    this->music.openFromFile("sounds/cityRuins.wav");
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::display(sf::RenderWindow &window, sf::Font font, current_game_state &state, sf::Text &pause)
{
    if(!music_launched)
    {
        music_launched = true;
        this->music.play();
    }

    if(this->escapePressed)
    {
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            this->escapePressed = false;
        }
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        state.state = PAUSE;

        this->escapePressed = true;
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
    grid.display_score(window, font);
    grid.display_tetr_to_come(window);
    this->display_level(window, font);

    this->manage_rotation(state);
    this->manage_left_and_right(state);
    this->manage_tetromino_falling(state);
    this->manage_instant_falling(state);
    this->manage_quick_falling(state);
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::manage_rotation(current_game_state &state)
{
    // Rotation gauche
    if(this->Wpressed)
    {
        if(!sf::Keyboard::isKeyPressed(state.controls[LEFT_ROTATION]))
        {
            this->Wpressed = false;
        }
    }

    else if(sf::Keyboard::isKeyPressed(state.controls[LEFT_ROTATION]))
    {
        grid.rotate('L');
        this->Wpressed = true;
    }

    // Rotation droite
    if(this->UpPressed)
    {
        if(!sf::Keyboard::isKeyPressed(state.controls[RIGHT_ROTATION]))
        {
            this->UpPressed = false;
        }
    }

    else if(sf::Keyboard::isKeyPressed(state.controls[RIGHT_ROTATION]))
    {
        grid.rotate('R');
        this->UpPressed = true;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::manage_left_and_right(current_game_state &state)
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

void Gameplay::manage_tetromino_falling(current_game_state &state)
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

void Gameplay::manage_instant_falling(current_game_state &state)
{
    if(this->spacePressed)
    {
        if(!sf::Keyboard::isKeyPressed(state.controls[INSTANT_DESCENT]))
        {
            this->spacePressed = false;
        }
    }

    else if(sf::Keyboard::isKeyPressed(state.controls[INSTANT_DESCENT]))
    {
        grid.go_down();
        this->spacePressed = true;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::manage_quick_falling(current_game_state &state)
{
    if(this->DownPressed)
    {
        if(!sf::Keyboard::isKeyPressed(state.controls[QUICK_DESCENT]))
        {
            this->speed*=4;
            this->DownPressed = false;
        }
    }

    else if(sf::Keyboard::isKeyPressed(state.controls[QUICK_DESCENT]))
    {
        this->speed/=4;
        this->DownPressed = true;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Gameplay::display_level(sf::RenderWindow &window, sf::Font &font)
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