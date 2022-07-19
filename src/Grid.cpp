#include "headers/grid.hpp"
#include <random>
#include <iostream> // temporaire

Grid::Grid()
{
	this->reset();

	this->m_textures[I_SHAPE].loadFromFile("textures/caseI.png");
	this->m_textures[J_SHAPE].loadFromFile("textures/caseJ.png");
	this->m_textures[L_SHAPE].loadFromFile("textures/caseL.png");
	this->m_textures[Z_SHAPE].loadFromFile("textures/caseZ.png");
	this->m_textures[T_SHAPE].loadFromFile("textures/caseT.png");
	this->m_textures[S_SHAPE].loadFromFile("textures/caseS.png");
	this->m_textures[O_SHAPE].loadFromFile("textures/caseO.png");
	this->m_textures[GHOST].loadFromFile("textures/caseG.png");
	this->m_textures[EMPTY].loadFromFile("textures/grid.png");
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::reset()
{
	this->m_fall_timer = 0;
	this->m_move_timer = 0;
	this->m_tetroSet = false;
	this->m_rightRotateKeyPressed = false;
	this->m_leftRotateKeyPressed = false;
	this->m_instantDescentKeyPressed = false;
	this->m_holdKeyPressed = false;
	this->m_pauseKeyPressed = false;
	this->m_nb_selected_tetros = 0;
	this->m_can_use_hold = true;
	this->m_tetros_in_hold = EMPTY;
	this->m_game_over = false;

	for (char i = 0; i < GRID_WIDTH; i++)
		for (char j = 0; j < GRID_HEIGHT; j++)
			this->m_grid[i][j] = EMPTY;

	this->m_tetros_selected = setAllCAsesAt(this->m_tetros_selected, EMPTY);

	//for (unsigned char i = 0; i < this->m_tetros_selected.size(); i++)
	//	this->m_tetros_selected[i] = EMPTY;

	for (unsigned char i = 0; i < this->m_tetros_to_come.size(); i++)
		this->m_tetros_to_come[i] = this->get_random_tetromino();
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::manage_events(sf::RenderWindow& window, currentGameState& state)
{
	// Set game over screen
	if (this->m_game_over)
	{
		state.state = GAME_OVER;
	}

	// Set pause screen
	if (keyPressed(this->m_pauseKeyPressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
	{
		state.state = PAUSE;
	}

	// Set a tetromino when the previous is put
	if (!this->m_tetroSet)
	{
		this->set_tetromino(false);
	}

	this->manage_descent(state);

	// Manage left and right moves
	this->manage_direction_moves(state);

	// Manage the rotation of the tetromino
	if (keyPressed(this->m_rightRotateKeyPressed, sf::Keyboard::isKeyPressed(state.controls[RIGHT_ROTATION])))
	{
		this->rotate('R');
	}
	else if (keyPressed(this->m_leftRotateKeyPressed, sf::Keyboard::isKeyPressed(state.controls[LEFT_ROTATION])))
	{
		this->rotate('L');
	}

	// Put the tetromino down
	if (keyPressed(this->m_instantDescentKeyPressed, sf::Keyboard::isKeyPressed(state.controls[INSTANT_DESCENT])))
	{
		this->set_tetro_down();
	}

	// Put the tetromino in the hold
	if (keyPressed(this->m_holdKeyPressed, sf::Keyboard::isKeyPressed(state.controls[HOLD]) && m_can_use_hold))
	{
		this->use_hold();
	}

	this->display_all(window);
}

void Grid::manage_descent(currentGameState& state)
{
	char speed = 16;

	if (sf::Keyboard::isKeyPressed(state.controls[QUICK_DESCENT]))
	{
		speed = 4;
	}

	// fall_timer for the tetromino
	if (this->m_fall_timer == 0)
	{
		this->m_fall_timer = 1;

		if (this->check_next_pos(this->m_hitablePoints, 0, 1))
		{
			this->move_next_pos(this->m_hitablePoints, 0, 1);
		}
		else
		{
			this->landing();
		}
	}
	else
	{
		this->m_fall_timer = (1 + this->m_fall_timer) % speed;
	}
}

void Grid::manage_direction_moves(currentGameState& state)
{
	if (this->m_move_timer == 0)
	{
		// Move the tetromino to the left
		if (sf::Keyboard::isKeyPressed(state.controls[MOVE_LEFT]) && this->check_next_pos(this->m_hitablePoints, -1, 0))
		{
			this->move_next_pos(this->m_hitablePoints, -1, 0);
		}
		// Move the tetromino to the right
		else if (sf::Keyboard::isKeyPressed(state.controls[MOVE_RIGHT]) && this->check_next_pos(this->m_hitablePoints, 1, 0))
		{
			this->move_next_pos(this->m_hitablePoints, 1, 0);
		}

		this->m_move_timer = 1;
	}
	else
	{
		this->m_move_timer = (1 + this->m_move_timer) % 5;
	}
}

void Grid::set_tetro_down()
{
	this->replace_cases(this->m_posToDelete, CURRENT_BLOCK, EMPTY);
	this->m_hitablePoints = this->get_ghost_pos();
	this->actualize_tetr_position();
	this->landing();
}

void Grid::display_all(sf::RenderWindow& window)
{
	this->display_grid(window);
	this->display_tetr_to_come(window);
	this->display_hold(window);
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::replace_cases(std::array<sf::Vector2i, 4>& positions, char casetype_to_replace, char replacing_case)
{
	for (char i = 0; i < positions.size(); i++)
		if (this->m_grid[positions[i].y][positions[i].x] == casetype_to_replace)
			this->m_grid[positions[i].y][positions[i].x] = replacing_case;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::actualize_tetr_position()
{
	// Empty the actual m_ghost
	this->replace_cases(this->m_ghost, GHOST, EMPTY);

	// Create the new m_ghost at the new position
	this->m_ghost = this->get_ghost_pos();
	this->replace_cases(this->m_ghost, EMPTY, GHOST);

	// Move the current tetromino to the good position
	for (char i = 0; i < 4; i++) 
		this->m_grid[this->m_hitablePoints[i].y][this->m_hitablePoints[i].x] = CURRENT_BLOCK;

	this->m_posToDelete = this->m_hitablePoints;
}

/*--------------------------------------------------------------------------------------------------------*/

char Grid::get_random_tetromino()
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<short> distr(0, 6);

	if (this->m_nb_selected_tetros == this->m_tetros_selected.size())
	{
		this->m_tetros_selected = setAllCAsesAt(this->m_tetros_selected, EMPTY);

		this->m_nb_selected_tetros = 0;
	}

	char random_tetr = distr(eng);

	while (isPresentIn(this->m_tetros_selected, random_tetr))
	{
		random_tetr = distr(eng);
	}

	this->m_tetros_selected[this->m_nb_selected_tetros] = random_tetr;
	this->m_nb_selected_tetros++;

	return random_tetr;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::display_grid(sf::RenderWindow& window)
{
	sf::Sprite cell;

	// Display the m_grid
	for (char i = 0; i < GRID_WIDTH; i++)
	{
		for (char j = 0; j < GRID_HEIGHT; j++)
		{
			cell.setPosition(j * CASE_SIZE, i * CASE_SIZE);

			if (this->m_grid[i][j] == EMPTY)
				cell.setTexture(this->m_textures[EMPTY]);
			else if (this->m_grid[i][j] == CURRENT_BLOCK) 
				cell.setTexture(this->m_textures[this->m_tetros_to_come[0]]);
			else if (this->m_grid[i][j] == GHOST)
				cell.setTexture(this->m_textures[GHOST]);
			else
				cell.setTexture(this->m_textures[this->m_grid[i][j]]);

			window.draw(cell);
		}
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::display_tetr_to_come(sf::RenderWindow& window)
{
	sf::Sprite cell;
	cell.setScale(sf::Vector2f(0.5f, 0.5f));

	for (unsigned char k = 1; k < 7; k++) // For each tetrominos to come 
	{
		sf::Vector2i corner(3, 0);
		if (this->m_tetros_to_come[k] == I_SHAPE) corner = sf::Vector2i(3, -1);

		// Create the matrix corresponding to the k tetromino to come
		std::vector<std::vector<char>> matrix_tetr_to_come = pos_to_matrix(
			set_positions(this->m_tetros_to_come[k]), 
			this->m_tetros_to_come[k], corner
		);

		display_matrix
		(
			window,
			matrix_tetr_to_come,
			TETR_TO_COME_X,
			TETR_TO_COME_Y + 3 * k * NEXT,
			cell,
			this->m_textures[this->m_tetros_to_come[k]],
			CURRENT_BLOCK
		);
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::display_hold(sf::RenderWindow& window)
{
	sf::Sprite cell;
	cell.setScale(sf::Vector2f(0.5f, 0.5f));

	if (this->m_tetros_in_hold != EMPTY)
	{
		sf::Vector2i corner(3, 0);
		if (this->m_tetros_in_hold == I_SHAPE) corner = sf::Vector2i(3, -1);

		std::vector<std::vector<char>> matrix_held_tetr = pos_to_matrix(
			set_positions(this->m_tetros_in_hold), 
			this->m_tetros_in_hold, 
			corner
		);

		display_matrix
		(
			window,
			matrix_held_tetr,
			HOLDING_PLACE_X,
			HOLDING_PLACE_Y,
			cell,
			this->m_textures[this->m_tetros_in_hold],
			CURRENT_BLOCK
		);
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::set_tetromino(bool for_hold)
{
	if (!for_hold) 
		for (unsigned char i = 0; i < this->m_tetros_to_come.size() - 1; i++) 
			this->m_tetros_to_come[i] = this->m_tetros_to_come[i + 1];

	this->m_tetros_to_come[this->m_tetros_to_come.size() - 1] = get_random_tetromino();

	std::array<sf::Vector2i, 4> positions = this->set_positions(this->m_tetros_to_come[0]);

	for (unsigned char i = 0; i < 4; i++)
	{
		if (this->m_grid[positions[i].y][positions[i].x] >= I_SHAPE 
			&& this->m_grid[positions[i].y][positions[i].x] <= O_SHAPE)
		{
			this->m_game_over = true;
		}
	}

	if (!this->m_game_over)
	{
		this->m_hitablePoints = positions;

		this->m_posToDelete = this->m_hitablePoints;

		this->m_leftHandCorner = sf::Vector2i(3, 0);

		if (this->m_tetros_to_come[0] == I_SHAPE) this->m_leftHandCorner = sf::Vector2i(3, -1);

		this->set_matrix();

		this->actualize_tetr_position();

		this->m_tetroSet = true;
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::set_matrix()
{
	char size = this->m_current_tetros_matrix.size();

	// Reset the actual tetrmino matrix
	for (char i = size - 1; i >= 0; i--)
	{
		for (char j = 0; j < size; j++) this->m_current_tetros_matrix[i].pop_back();

		this->m_current_tetros_matrix.pop_back();
	}

	this->m_current_tetros_matrix = this->pos_to_matrix(
		this->m_hitablePoints, 
		this->m_tetros_to_come[0], 
		this->m_leftHandCorner
	);
}

/*--------------------------------------------------------------------------------------------------------*/

std::array<sf::Vector2i, 4> Grid::set_positions(char shape)
{
	std::array<sf::Vector2i, 4> positions;

	switch (shape)
	{
	case I_SHAPE:
		positions = { sf::Vector2i(3,0), sf::Vector2i(4,0), sf::Vector2i(5,0), sf::Vector2i(6,0) };
		break;

	case J_SHAPE:
		positions = { sf::Vector2i(3,0), sf::Vector2i(3,1), sf::Vector2i(4,1), sf::Vector2i(5,1) };
		break;

	case L_SHAPE:
		positions = { sf::Vector2i(5,0), sf::Vector2i(3,1), sf::Vector2i(4,1), sf::Vector2i(5,1) };
		break;

	case Z_SHAPE:
		positions = { sf::Vector2i(3,0), sf::Vector2i(4,0), sf::Vector2i(4,1), sf::Vector2i(5,1) };
		break;

	case T_SHAPE:
		positions = { sf::Vector2i(4,0), sf::Vector2i(3,1), sf::Vector2i(4,1), sf::Vector2i(5,1) };
		break;

	case S_SHAPE:
		positions = { sf::Vector2i(4,0), sf::Vector2i(5,0), sf::Vector2i(3,1), sf::Vector2i(4,1) };
		break;

	case O_SHAPE:
		positions = { sf::Vector2i(4,0), sf::Vector2i(5,0), sf::Vector2i(4,1), sf::Vector2i(5,1) };
		break;
	}

	return positions;
}

/*--------------------------------------------------------------------------------------------------------*/

bool Grid::check_next_pos(std::array<sf::Vector2i, 4> coordinates, char x, char y)
{
	for (unsigned char i = 0; i < 4; i++)
	{
		coordinates[i].x += x;
		coordinates[i].y += y;
	}

	return check_set_pos(coordinates);
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::move_next_pos(std::array<sf::Vector2i, 4>& coordinates, char x, char y)
{
	this->replace_cases(this->m_posToDelete, CURRENT_BLOCK, EMPTY);

	for (char i = 0; i < 4; i++)
	{
		coordinates[i].x += x;
		coordinates[i].y += y;
	}

	this->actualize_tetr_position();

	if (coordinates == this->m_hitablePoints)
	{
		this->m_leftHandCorner.x += x;
		this->m_leftHandCorner.y += y;
	}
}

/*--------------------------------------------------------------------------------------------------------*/

bool Grid::check_rotate(char side)
{
	if (this->m_tetros_to_come[0] == O_SHAPE) return false;

	bool can_rotate = true;

	std::vector<std::vector<char>> test_matrix = rotate_matrix(this->m_current_tetros_matrix, side);

	unsigned char i = 0;

	std::array<sf::Vector2i, 4> positions = this->matrix_to_pos(test_matrix);

	can_rotate = this->check_set_pos(this->matrix_to_pos(test_matrix));

	if (!can_rotate) can_rotate = this->wall_kick(test_matrix);

	return can_rotate;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::rotate(char side)
{
	if (!this->check_rotate(side)) return;

	this->replace_cases(this->m_posToDelete, CURRENT_BLOCK, EMPTY);

	this->m_current_tetros_matrix = rotate_matrix(this->m_current_tetros_matrix, side);

	this->m_hitablePoints = this->matrix_to_pos(this->m_current_tetros_matrix);

	this->actualize_tetr_position();
}

/*--------------------------------------------------------------------------------------------------------*/

bool Grid::wall_kick(std::vector<std::vector<char>> test_matrix)
{
	std::array<sf::Vector2i, 4> positions = this->matrix_to_pos(test_matrix);

	if (this->check_next_pos(positions, 1, 0))
	{
		// Move the artificials positions on the right
		this->move_next_pos(positions, 1, 0);

		this->m_leftHandCorner.x++;

		this->m_hitablePoints = positions;

		return true;
	}

	// The same thing for the left
	else if (this->check_next_pos(positions, -1, 0))
	{
		this->move_next_pos(positions, -1, 0);

		this->m_leftHandCorner.x--;

		this->m_hitablePoints = positions;

		return true;
	}

	// If a single move right or left is not enough
	else if (this->m_tetros_to_come[0] == I_SHAPE)
	{
		// Check for the right movement
		this->move_next_pos(positions, 2, 0);

		if (this->check_set_pos(positions))
		{
			this->m_posToDelete = this->m_hitablePoints;

			this->move_next_pos(this->m_hitablePoints, 2, 0);

			return true;
		}

		// Check for the left movement
		this->move_next_pos(positions, -4, 0);

		if (this->check_set_pos(positions))
		{
			this->m_posToDelete = this->m_hitablePoints;

			this->move_next_pos(this->m_hitablePoints, -2, 0);

			return true;
		}
	}

	return false;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::clear_lines()
{
	for (unsigned char i = 0; i < GRID_WIDTH; i++)
	{
		if (!(isPresentIn(this->m_grid[i], EMPTY) || isPresentIn(this->m_grid[i], GHOST)))
		{
			this->m_grid[i] = setAllCAsesAt(this->m_grid[i], EMPTY);

			for (unsigned char j = i; j > 0; j--)
				for (unsigned char k = 0; k < GRID_HEIGHT; k++)
					this->m_grid[j][k] = this->m_grid[j - 1][k];
		}
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::landing()
{
	for (char i = 0; i < m_hitablePoints.size(); i++)
		this->m_grid[this->m_hitablePoints[i].y][this->m_hitablePoints[i].x] = this->m_tetros_to_come[0];

	this->m_tetroSet = false;

	this->clear_lines();

	if (!this->m_can_use_hold) m_can_use_hold = true;
}

/*--------------------------------------------------------------------------------------------------------*/

bool Grid::check_set_pos(std::array<sf::Vector2i, 4> positions)
{
	for(sf::Vector2i position : positions)
	{
		if (this->is_cell_out(position.x, position.y)
			|| this->is_cell_filled(position.x, position.y))
		{
			return false;
		}
	}

	return true;
}

bool Grid::is_cell_out(int x, int y)
{
	if (x < 0) return true;
	if (x > 9) return true;
	if (y < 0) return true;
	if (y > 19) return true;

	return false;
}

bool Grid::is_cell_filled(int x, int y)
{
	if (this->m_grid[y][x] >= I_SHAPE 
		&& this->m_grid[y][x] <= O_SHAPE)
	{
		return true;
	}

	return false;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::use_hold()
{
	this->replace_cases(this->m_hitablePoints, CURRENT_BLOCK, EMPTY);
	this->replace_cases(this->m_ghost, GHOST, EMPTY);

	if (this->m_tetros_in_hold == EMPTY)
	{
		this->m_tetros_in_hold = this->m_tetros_to_come[0];
		this->set_tetromino(false);
	}
	else
	{
		char temp = this->m_tetros_to_come[0];
		this->m_tetros_to_come[0] = this->m_tetros_in_hold;
		this->m_tetros_in_hold = temp;
		this->set_tetromino(true);
	}

	this->m_can_use_hold = false;
}

/*--------------------------------------------------------------------------------------------------------*/

std::array<sf::Vector2i, 4> Grid::matrix_to_pos(std::vector<std::vector<char>> matrix)
{
	unsigned char k = 0;
	std::array<sf::Vector2i, 4> pos;

	for (unsigned char i = 0; i < matrix.size(); i++)
	{
		for (unsigned char j = 0; j < matrix[0].size(); j++)
		{
			if (matrix[i][j] == CURRENT_BLOCK)
			{
				pos[k].x = j + this->m_leftHandCorner.x;
				pos[k].y = i + this->m_leftHandCorner.y;

				k++;
			}
		}
	}

	return pos;
}

/*--------------------------------------------------------------------------------------------------------*/

std::vector<std::vector<char>> Grid::pos_to_matrix(std::array<sf::Vector2i, 4> positions, char shape, sf::Vector2i corner)
{
	std::vector<std::vector<char>> matrix;

	char size = 3;

	if (shape == I_SHAPE) size = 4;

	for (unsigned char i = 0; i < size; i++)
	{
		std::vector<char> matrix_line;

		for (unsigned char j = 0; j < size; j++) matrix_line.push_back(0);

		matrix.push_back(matrix_line);
	}

	for (sf::Vector2i position : positions) 
		matrix[position.y - corner.y][position.x - corner.x] = CURRENT_BLOCK;

	return matrix;
}

/*--------------------------------------------------------------------------------------------------------*/

std::array<sf::Vector2i, 4> Grid::get_ghost_pos()
{
	std::array<sf::Vector2i, 4> positions = this->m_hitablePoints;

	while (this->check_next_pos(positions, 0, 1)) 
		for (unsigned char i = 0; i < 4; i++) 
			positions[i].y++;

	return positions;
}

/*--------------------------------------------------------------------------------------------------------*/