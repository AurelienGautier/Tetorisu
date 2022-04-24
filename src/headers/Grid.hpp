#pragma once

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Global.hpp"

enum
{
	I_SHAPE,
	J_SHAPE,
	L_SHAPE,
	Z_SHAPE,
	T_SHAPE,
	S_SHAPE,
	O_SHAPE,
	GHOST,
	EMPTY,
	CURRENT_BLOCK
};

class Grid
{
private:
	std::array<sf::Vector2i, 4> m_hitablePoints;
	std::array<sf::Vector2i, 4> posToDelete;
	std::array<sf::Vector2i, 4> ghost;
	std::array<std::array<int, GRID_HEIGHT>, GRID_WIDTH> grid;
	std::array<sf::Color, 9> colours;
	char fall_timer;
	char move_timer;
	bool tetroSet;
	sf::Vector2i leftHandCorner;
	bool rightRotateKeyPressed;
	bool leftRotateKeyPressed;
	bool instantDescentKeyPressed;
	bool holdKeyPressed;
	bool pauseKeyPressed;
	std::vector<std::vector<char>> current_tetros_matrix;
	std::array<char, 7> tetros_to_come;
	std::array<char, 7> tetros_selected;
	char nb_selected_tetros;
	bool can_use_hold;
	char tetros_in_hold;
	bool game_over;
	char tetro_fall_speed;

	void replace_cases(std::array<sf::Vector2i, 4>& positions, char casetype_to_replace, char replacing_case);
	void actualize_tetr_position();
	char get_random_tetromino();
	void display_grid(sf::RenderWindow& window);
	void display_tetr_to_come(sf::RenderWindow& window);
	void display_hold(sf::RenderWindow& window);
	void set_tetromino(bool for_hold);
	void set_matrix();
	std::array<sf::Vector2i, 4> set_positions(char shape);
	bool check_next_pos(std::array<sf::Vector2i, 4> coordinates, char x, char y);
	void move_next_pos(std::array<sf::Vector2i, 4>& coordinates, char x, char y);
	bool check_rotate(char side);
	void rotate(char side);
	bool wall_kick(std::vector<std::vector<char>> test_matrix);
	void clear_lines();
	void landing();
	bool check_set_pos(std::array<sf::Vector2i, 4> positions);
	void use_hold();
	std::array<sf::Vector2i, 4> matrix_to_pos(std::vector<std::vector<char>> matrix);
	std::vector<std::vector<char>> pos_to_matrix(std::array<sf::Vector2i, 4> pos, char shape, sf::Vector2i corner);
	std::array<sf::Vector2i, 4> get_ghost_pos();

public:
	void reset();
	Grid();
	void manage_events(sf::RenderWindow& window, currentGameState& state);
};
