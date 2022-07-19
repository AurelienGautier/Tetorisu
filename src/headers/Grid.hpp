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
	// The position of the current tetromino squares
	std::array<sf::Vector2i, 4> m_hitablePoints;

	// The position of the tetromino squares to delete from the grid
	std::array<sf::Vector2i, 4> m_posToDelete;

	// The position of the ghost squares
	std::array<sf::Vector2i, 4> m_ghost;

	// The matrix containing every element of the grid
	std::array<std::array<int, GRID_HEIGHT>, GRID_WIDTH> m_grid;

	// The textures of the game to load
	std::array<sf::Texture, 9> m_textures;

	// Timer between each descent of the current tetromino
	char m_fall_timer;

	// Timer between each left or right move for the tetromino
	char m_move_timer;

	// Say if the current tetromino is set
	bool m_tetroSet;

	// The left hand corner of the current tetromino
	sf::Vector2i m_leftHandCorner;

	// The booleans allowing to know if a key is pressed
	bool m_rightRotateKeyPressed;
	bool m_leftRotateKeyPressed;
	bool m_instantDescentKeyPressed;
	bool m_holdKeyPressed;
	bool m_pauseKeyPressed;

	// The current tetromino represented as a matrix
	std::vector<std::vector<char>> m_current_tetros_matrix;

	// The actual tetromino and the tetrominos that will come after
	std::array<char, 7> m_tetros_to_come;

	// The tetromino that cannot be selected for now
	std::array<char, 7> m_tetros_selected;

	// The number of tetrominos that cannot be selected for now
	char m_nb_selected_tetros;

	// Say if the hold can be used
	bool m_can_use_hold;

	// The tetromino that is in the hold
	char m_tetros_in_hold;

	// Say if the game is finished or not
	bool m_game_over;

	void replace_cases(std::array<sf::Vector2i, 4>& positions, char casetype_to_replace, char replacing_case);
	void actualize_tetr_position();
	char get_random_tetromino();
	void display_grid(sf::RenderWindow& window);
	void display_tetr_to_come(sf::RenderWindow& window);
	void display_hold(sf::RenderWindow& window);
	void set_tetromino(bool for_hold);
	void set_matrix();
	std::array<sf::Vector2i, 4> set_positions(char shape);
	void move_next_pos(std::array<sf::Vector2i, 4>& coordinates, char x, char y);
	void rotate(char side);
	bool wall_kick(std::vector<std::vector<char>> test_matrix);
	void clear_lines();
	void landing();
	void use_hold();
	std::array<sf::Vector2i, 4> matrix_to_pos(std::vector<std::vector<char>> matrix);
	std::vector<std::vector<char>> pos_to_matrix(std::array<sf::Vector2i, 4> pos, char shape, sf::Vector2i corner);
	std::array<sf::Vector2i, 4> get_ghost_pos();

	// Functions to manage events
	void manage_descent(currentGameState& state);
	void manage_direction_moves(currentGameState& state);
	void set_tetro_down();
	void display_all(sf::RenderWindow& window);

	// Functions to check if a position of a tetromino is correct
	bool check_set_pos(std::array<sf::Vector2i, 4> positions);
	bool is_cell_out(int x, int y);
	bool is_cell_filled(int x, int y);
	bool check_next_pos(std::array<sf::Vector2i, 4> coordinates, char x, char y);
	bool check_rotate(char side);

public:
	void reset();
	Grid();
	void manage_events(sf::RenderWindow& window, currentGameState& state);
};
