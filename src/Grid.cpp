#include "headers/global.hpp"
#include "headers/Grid.hpp"
#include <iostream>
#include <random>
#include <chrono>

Grid::Grid()
{
    this->textures[0].loadFromFile("textures/caseI.png");
    this->textures[1].loadFromFile("textures/caseJ.png");
    this->textures[2].loadFromFile("textures/caseL.png");
    this->textures[3].loadFromFile("textures/caseZ.png");
    this->textures[4].loadFromFile("textures/caseT.png");
    this->textures[5].loadFromFile("textures/caseS.png");
    this->textures[6].loadFromFile("textures/caseO.png");
    this->textures[7].loadFromFile("textures/grid.png");

    this->reset();
}

/*--------------------------------------------------------------------------------------------------------------*/

bool Grid::initialize_tetromino()
{
    // Définit le nouveau tetromino à la position 0
    this->current_position = 0;

    // Décale tous les tetromino vers le début
    for (char i = 0; i < 6; i++)
    {
        this->current_tetrominos[i] = current_tetrominos[i+1];
    }
    
    // Regenère le dernier tetromino
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<char> distribution(0, 6);
    this->current_tetrominos[6] = distribution(engine);

    // Charge le tetromino
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            this->tetromino.matrice[i][j] = this->tetromino.tetrominos[current_tetrominos[0]][0][i][j];
        }
    }

    // Le précédent tetromino est posé et on en crée un nouveau que l'on place en haut au milieu
    this->tetromino.position_x = 3;
    this->tetromino.position_y = 0;

    // Permet d'afficher le tetromino à la bonne ligne
    for (char i = 0; i < 4; i++) // Parcourt la matrice composant le tetromino
    {
        bool filledLine = false; // Permet de savoir si la ligne possède un morceau de tetromino

        for (char j = 0; j < 4; j++)
        {
            if(tetromino.matrice[i][j] == 2)
            {
                filledLine = true;
            }
        }

        if(filledLine)
        {
            break;
        }

        else //Si la ligne est vide
        {
            this->tetromino.position_y--;
        }
    }

    // Vérifie si game_over ou non
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            if(this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] == 1 && tetromino.matrice[i][j] == 2)
            {
                return false;
            }
        }
    }

    // Permet d'autoriser les mouvements horizontaux
    this->horizontal_move = true;

    // Permet d'autoriser la rotation
    this->rotation_enabled = true;

    return true;
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::display_grid(sf::RenderWindow &window) 
{
    // Crée des rectangles pour cacher le fond dans la grille
    sf::RectangleShape rectangles;
    for (char i = 0; i < 20; i++)
    {
        rectangles.setSize(sf::Vector2f(CASE_SIZE*10, CASE_SIZE));
        rectangles.setFillColor(sf::Color::Black);
    }
    

    for (char i = 0; i < 20; i++)
    {
        rectangles.setPosition((window.getSize().x/2 - CASE_SIZE*5), (window.getSize().y/2 - CASE_SIZE*10)+i*CASE_SIZE);
        window.draw(rectangles);

        for (char j = 0; j < 10; j++)
        {
            if(matrice[i][j] == 2)
            {
                this->displayed_textures[i][j] = this->textures[current_tetrominos[0]];
            }

            this->cases.setPosition(GRID_CASE_POSITION_X, GRID_CASE_POSITION_Y);
            this->cases.setTexture(this->displayed_textures[i][j]);
            window.draw(cases);
        }
    }

    display_tetromino();
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::display_tetromino() 
{
    // Boucle permettant de positionner le tetromino au bon endroit dans la grille
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            if(this->tetromino.matrice[i][j] == 2) 
            {
                this->matrice[tetromino.position_y + i][this->tetromino.position_x + j] = this->tetromino.matrice[i][j];
            }
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::move_tetromino_left() 
{
    if(this->check_left() && this->horizontal_move)
    {
        this->horizontal_move = false;
        
        for (char i = 0; i < 4; i++)
        {
            for (char j = 0; j < 4; j++)
            {
                if (this->tetromino.matrice[i][j] == 2)
                {
                    // Bouge le tetromino et les textures
                    this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j-1] = 2;
                    this->displayed_textures[this->tetromino.position_y+i][this->tetromino.position_x+j-1] = this->textures[this->current_tetrominos[0]];

                    this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] = 0;
                    this->displayed_textures[this->tetromino.position_y+i][this->tetromino.position_x+j] = this->textures[7];
                }
            }
        }

        this->tetromino.position_x--;

        this->horizontal_move = true;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

bool Grid::check_left()
{
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            if(this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] == 2 && (this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j-1] == 1 || this->tetromino.position_x+j-1 < 0))
            {
                return false;
            }
        }
    }

    return true;
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::move_tetromino_right()
{
    if(this->check_right() && this->horizontal_move)
    {
        // On empêche le mouvement horizontal afin d'éviter que plusieurs déplacements se fassent simultanément
        this->horizontal_move = false;

        
        for (char i = 3; i >= 0; i--)
        {
            for (char j = 3; j >= 0; j--)
            {
                if (this->tetromino.matrice[i][j] == 2)
                {
                    // Bouge le tetromino ainsi que ses textures
                    this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j+1] = 2;
                    this->displayed_textures[this->tetromino.position_y+i][this->tetromino.position_x+j+1] = this->textures[this->current_tetrominos[0]];

                    this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] = 0;
                    this->displayed_textures[this->tetromino.position_y+i][this->tetromino.position_x+j] = this->textures[7];
                }
            }
        }

        this->tetromino.position_x ++;

        // Et on autorise le mouvement horizontal
        this->horizontal_move = true;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

bool Grid::check_right()
{
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            if(this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] == 2 && (this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j+1] == 1 || this->tetromino.position_x+j+1 > 9))
            {
                return false;
            }
        }
    }

    return true;
}

/*--------------------------------------------------------------------------------------------------------------*/

bool Grid::fall_tetromino()
{
    // Si il n'y a pas de tetromino ni le sol en dessous
    if(this->check_fall())
    {
        // On déplace le tetromino d'une case vers le bas
        for (char i = 3; i >= 0; i--)
        {
            for (char j = 3; j >= 0; j--)
            {
                if(this->tetromino.matrice[i][j] == 2)
                {
                    // Bouge le tetromino ainsi que les textures
                    this->matrice[this->tetromino.position_y+i+1][this->tetromino.position_x+j] = 2;
                    this->displayed_textures[this->tetromino.position_y+i+1][this->tetromino.position_x+j] = this->textures[this->current_tetrominos[0]];

                    this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] = 0;
                    this->displayed_textures[this->tetromino.position_y+i][this->tetromino.position_x+j] = this->textures[7];
                }
            }
        }

        this->tetromino.position_y++;
    }

    else
    {
        // Permet au tetromino d'atterrir et de ne plus être celui contrôlé par le joueur
        this->landing();

        // On supprime les lignes pleines s'il y en a
        this->clear_lines();

        // Et on permet à un nouveau tetromino d'apparaître
        return this->initialize_tetromino();
    }

    return true;
}

/*--------------------------------------------------------------------------------------------------------------*/

bool Grid::check_fall()
{
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            if(this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] == 2 && (this->matrice[this->tetromino.position_y+i+1][this->tetromino.position_x+j] == 1 || this->tetromino.position_y+i+1 > 19))
            {
                return false;
            }
        }
    }

    return true;
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::landing()
{
    // Permet un petit délai avnat l'atterrissage
    int time(0), speed(16);
    bool ok(false);

    if(time == 0)
    {
        time = 1;
        ok = true;
    }

    else
    {
        time = (1 + time) % speed;
    }

    if(ok)
    {
        // Empêche la rotation du tetromino pour empêcher les bugs
        this->rotation_enabled = false;

        // On empêche le mouvement du tetromino le temps de l'atterrissage afin d'empêcher les bugs
        this->horizontal_move = false;

        for (char i = 0; i < 20; i++)
        {
            for (char j = 0; j < 10; j++)
            {
                if(this->matrice[i][j] == 2)
                {
                    this->matrice[i][j] = 1;
                }
            }
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::clear_lines()
{
    // Boucle regardant chaque ligne
    for (char i = 0; i < 20; i++)
    {
        bool filled_line(true);

        // Boucle regardant chaque colonne de la ligne sélectionnée
        char j=0;
        while(j<10 && filled_line)
        {
            if (this->matrice[i][j] == 0)
            {
                filled_line = false;
            }

            j++;
        }

        // Si la ligne est à supprimer
        if(filled_line)
        {
            this->score += 100;

            // Supprime la ligne
            for (char j = 0; j < 10; j++)
            {
                this->matrice[i][j] = 0;
                this->displayed_textures[i][j] = this->textures[7];
            }

            // Décale vers le bas les lignes du dessus
            for (char j = i; j > 0; j--)
            {
                for (char k = 0; k < 10; k++)
                {
                    this->matrice[j][k] = this->matrice[j-1][k];
                    this->displayed_textures[j][k] = this->displayed_textures[j-1][k];
                }
            }
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::rotate(char side)
{
    if(this->check_rotate() && this->current_tetrominos[0]!=6 && this->rotation_enabled)
    {
        this->horizontal_move = false;

        // Si la rotation doit s'effectuer à droite
        if(side == 'R')
        {
            // Modifie la position
            if(this->current_position < 3)
            {
                this->current_position++;
            }

            else 
            {
                this->current_position = 0;
            }
        }

        // Si la rotation doit s'effectuer à gauche
        else if(side == 'L')
        {
            // Modifie la position
            if(this->current_position > 0)
            {
                this->current_position--;
            }

            else 
            {
                this->current_position = 3;
            }
        }

        // Réinitialise le tetromino
        for (char i = 0; i < 4; i++)
        {
            for (char j = 0; j < 4; j++)
            {
                if(this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] == 2)
                {
                    this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] = 0;
                    this->displayed_textures[this->tetromino.position_y+i][this->tetromino.position_x+j] = this->textures[7];
                }

                this->tetromino.matrice[i][j] = this->tetromino.tetrominos[this->current_tetrominos[0]][this->current_position][i][j];
            }   
        }

        // Le remplace avec le nouveau
        for (char i = 0; i < 4; i++)
        {
            for (char j = 0; j < 4; j++)
            {
                if (this->tetromino.matrice[i][j] == 2)
                {
                    this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] = 2;
                    this->displayed_textures[this->tetromino.position_y+i][this->tetromino.position_x+j] = this->textures[this->current_tetrominos[0]];
                }
            }
        }

        this->horizontal_move = true;
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

bool Grid::check_rotate()
{
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            if(this->tetromino.tetrominos[this->current_tetrominos[0]][this->current_position+1][i][j] == 2)
            {
                if(this->matrice[this->tetromino.position_y+i][this->tetromino.position_x+j] == 1 || 
                   this->tetromino.position_x+j < 0 || 
                   this->tetromino.position_x+j > 9 || 
                   this->tetromino.position_y+i > 19 || 
                   this->tetromino.position_y+i < 0)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

/*--------------------------------------------------------------------------------------------------------------*/

bool Grid::wallKick(char side)
{
    if(side == 'R')
    {

    }

    else if(side == 'L')
    {

    }

    else if(side == 'U')
    {

    }

    else if(side == 'D')
    {

    }

    return false;
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::go_down()
{
    this->horizontal_move = false;

    while(this->check_fall())
    {
        this->fall_tetromino();
    }

    this->landing();
    this->clear_lines();
    this->initialize_tetromino();
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::display_score(sf::RenderWindow &window, sf::Font font)
{
    sf::Text text("SCORE : " + std::to_string(score), font, 50);

    text.setPosition(SCORE_POSITION_X, SCORE_POSITION_Y);
    window.draw(text);
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::display_tetr_to_come(sf::RenderWindow &window)
{
    sf::RectangleShape background_hider;
    sf::Sprite sprite[4][4];

    for (char k = 1; k < 6; k++)
    {
        for (char i = 0; i < 4; i++)
        {
            background_hider.setSize(sf::Vector2f(CASE_SIZE,CASE_SIZE));
            background_hider.setFillColor(sf::Color::Black);

            for (char j = 0; j < 4; j++)
            {
                if(this->tetromino.tetrominos[this->current_tetrominos[k]][0][i][j] == 2)
                {
                    background_hider.setPosition(TETR_TO_COME_X+CASE_SIZE*j, (3*k*CASE_SIZE) + (TETR_TO_COME_Y+CASE_SIZE*i));
                    window.draw(background_hider);

                    sprite[i][j].setPosition(TETR_TO_COME_X+CASE_SIZE*j, (3*k*CASE_SIZE) + (TETR_TO_COME_Y+CASE_SIZE*i));
                    sprite[i][j].setTexture(this->textures[this->current_tetrominos[k]]);
                    window.draw(sprite[i][j]);
                }
            }
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::manage_hold(sf::RenderWindow &window)
{

}

/*--------------------------------------------------------------------------------------------------------------*/

void Grid::reset()
{
    this->horizontal_move = false;
    this->rotation_enabled = false;
    this->score = 0;

    for (char i = 0; i < 20; i++)
    {
        for (char j = 0; j < 10; j++)
        {
            this->matrice[i][j] = 0;
            this->displayed_textures[i][j] = this->textures[7];
        }
    }

    for (char i = 0; i < 6; i++)
    {
        // Choisit un nombre aléatoire
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::default_random_engine engine(seed + 3*i);
        std::uniform_int_distribution<char> distribution(0, 6);
        int randomNb = distribution(engine);

        // Modifie le nombre aléatoire si le tetromino correspondant est géjà généré
        for (char j = 0; j < i; j++)
        {
            if(randomNb == this->current_tetrominos[j])
            {
                if(randomNb == 6)
                    randomNb = 0;
                else
                    randomNb++;
            }
        }
        this->current_tetrominos[i] = randomNb;
    }

    this->initialize_tetromino();
}