#pragma once
#include <SFML/Graphics.hpp>

class Grid 
{
    public:
        Grid();
        bool initialize_tetromino(); // retourne false si le nouveau tetromino apparaît sur un autre (si game over)
        void display_grid(sf::RenderWindow &window);
        void display_tetromino();

        void move_tetromino_left();
        bool check_left();
        void move_tetromino_right();
        bool check_right();
        bool fall_tetromino(); // retourne false à la méthode manage_tetromino_falling (gameplay.cpp) si !initialize_tetromino
        bool check_fall();

        void landing();
        void clear_lines();

        void rotate(char side);
        bool check_rotate();
        bool wallKick(char side);

        void go_down();

        void display_score(sf::RenderWindow &window, sf::Font font);
        int get_score() {return this->score;}

        void display_tetr_to_come(sf::RenderWindow &window);
        void manage_hold(sf::RenderWindow &window);

        void reset(); // Initialise ou réinitialise tous les attributs afin de commencer ou recommencer une partie

    private:
        int matrice[20][10] = {0};
        sf::Sprite cases;

        sf::Texture displayed_textures[20][10];
        sf::Texture textures[8];

        bool horizontal_move, rotation_enabled;

        int current_tetrominos[7], current_position;
        struct current_tetromino {
            char matrice[4][4] = {0};

            char tetrominos[7][4][4][4] {
                {
                    {
                        {0,0,0,0},
                        {0,0,0,0},
                        {2,2,2,2},
                        {0,0,0,0}
                    },

                    {
                        {0,0,2,0},
                        {0,0,2,0},
                        {0,0,2,0},
                        {0,0,2,0}
                    },

                    {
                        {0,0,0,0},
                        {0,0,0,0},
                        {2,2,2,2},
                        {0,0,0,0}
                    },

                    {
                        {0,0,2,0},
                        {0,0,2,0},
                        {0,0,2,0},
                        {0,0,2,0}
                    }
                },

                {
                    {
                        {0,0,0,0},
                        {2,2,2,0},
                        {0,0,2,0},
                        {0,0,0,0}
                    },

                    {
                        {0,2,0,0},
                        {0,2,0,0},
                        {2,2,0,0},
                        {0,0,0,0}
                    },

                    {
                        {2,0,0,0},
                        {2,2,2,0},
                        {0,0,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,2,2,0},
                        {0,2,0,0},
                        {0,2,0,0},
                        {0,0,0,0}
                    }
                },

                {
                    {
                        {0,0,0,0},
                        {2,2,2,0},
                        {2,0,0,0},
                        {0,0,0,0}
                    },

                    {
                        {2,2,0,0},
                        {0,2,0,0},
                        {0,2,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,0,2,0},
                        {2,2,2,0},
                        {0,0,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,2,0,0},
                        {0,2,0,0},
                        {0,2,2,0},
                        {0,0,0,0}
                    }
                },

                {
                    {
                        {0,0,0,0},
                        {2,2,0,0},
                        {0,2,2,0},
                        {0,0,0,0}
                    },

                    {
                        {0,0,2,0},
                        {0,2,2,0},
                        {0,2,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,0,0,0},
                        {2,2,0,0},
                        {0,2,2,0},
                        {0,0,0,0}
                    },

                    {
                        {0,0,2,0},
                        {0,2,2,0},
                        {0,2,0,0},
                        {0,0,0,0}
                    }
                },

                {
                    {
                        {0,0,0,0},
                        {2,2,2,0},
                        {0,2,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,2,0,0},
                        {2,2,0,0},
                        {0,2,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,2,0,0},
                        {2,2,2,0},
                        {0,0,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,2,0,0},
                        {0,2,2,0},
                        {0,2,0,0},
                        {0,0,0,0}
                    }
                },

                {
                    {
                        {0,0,0,0},
                        {0,2,2,0},
                        {2,2,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,2,0,0},
                        {0,2,2,0},
                        {0,0,2,0},
                        {0,0,0,0}
                    },

                    {
                        {0,0,0,0},
                        {0,2,2,0},
                        {2,2,0,0},
                        {0,0,0,0}
                    },

                    {
                        {0,2,0,0},
                        {0,2,2,0},
                        {0,0,2,0},
                        {0,0,0,0}
                    }
                },

                {
                    {
                        {0,0,0,0},
                        {0,2,2,0},
                        {0,2,2,0},
                        {0,0,0,0}
                    },

                    {
                        {0,0,0,0},
                        {0,2,2,0},
                        {0,2,2,0},
                        {0,0,0,0}
                    },

                    {
                        {0,0,0,0},
                        {0,2,2,0},
                        {0,2,2,0},
                        {0,0,0,0}
                    },

                    {
                        {0,0,0,0},
                        {0,2,2,0},
                        {0,2,2,0},
                        {0,0,0,0}
                    }
                }
            };
            
            char position_x, position_y;
        };
        struct current_tetromino tetromino;

        int score;
};