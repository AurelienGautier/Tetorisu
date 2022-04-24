#include "headers/Grid.hpp"
#include <random>
#include <iostream> // temporaire

Grid::Grid()
{
	this->reset();

	this->colours[I_SHAPE] = sf::Color(0, 240, 240);
	this->colours[J_SHAPE] = sf::Color(0, 0, 240);
	this->colours[L_SHAPE] = sf::Color(240, 160, 0);
	this->colours[Z_SHAPE] = sf::Color(240, 0, 0);
	this->colours[T_SHAPE] = sf::Color(160, 0, 240);
	this->colours[S_SHAPE] = sf::Color(0, 240, 0);
	this->colours[O_SHAPE] = sf::Color(240, 240, 0);
	this->colours[GHOST]   = sf::Color(216, 223, 227);
	this->colours[EMPTY]   = sf::Color(60, 60, 60);
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::reset()
{
	this->fall_timer = 0;
	this->move_timer = 0;
	this->tetroSet = false;
	this->rightRotateKeyPressed = false;
	this->leftRotateKeyPressed = false;
	this->instantDescentKeyPressed = false;
	this->holdKeyPressed = false;
	this->pauseKeyPressed = false;
	this->nb_selected_tetros = 0;
	this->can_use_hold = true;
	this->tetros_in_hold = EMPTY;
	this->game_over = false;
	this->tetro_fall_speed = 16;

	for (char i = 0; i < GRID_WIDTH; i++) for (char j = 0; j < GRID_HEIGHT; j++) this->grid[i][j] = EMPTY;

	for (unsigned char i = 0; i < this->tetros_selected.size(); i++) this->tetros_selected[i] = EMPTY;

	for (unsigned char i = 0; i < this->tetros_to_come.size(); i++) this->tetros_to_come[i] = this->get_random_tetromino();
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::manage_events(sf::RenderWindow& window, currentGameState &state)
{
	char speed = 16;

	if (this->game_over) state.state = GAME_OVER;

	if (keyPressed(this->pauseKeyPressed, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) state.state = PAUSE;

	if (!this->tetroSet) this->set_tetromino(false);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) speed = 4;

	// fall_timer for the tetromino
	if (this->fall_timer == 0)
	{
		this->fall_timer = 1;

		if (this->check_next_pos(this->m_hitablePoints, 0, 1)) this->move_next_pos(this->m_hitablePoints, 0, 1);
		else this->landing();
	}
	else this->fall_timer = (1 + this->fall_timer) % speed;

	if (this->move_timer == 0)
	{
		// Move the tetromino to the left
		if (sf::Keyboard::isKeyPressed(state.controls[MOVE_LEFT]) && this->check_next_pos(this->m_hitablePoints, -1, 0))
			this->move_next_pos(this->m_hitablePoints, -1, 0);
		// Move the tetromino to the right
		else if (sf::Keyboard::isKeyPressed(state.controls[MOVE_RIGHT]) && this->check_next_pos(this->m_hitablePoints, 1, 0))
			this->move_next_pos(this->m_hitablePoints, 1, 0);

		this->move_timer = 1;
	}
	else this->move_timer = (1 + this->move_timer) % 5;

	if (keyPressed(this->rightRotateKeyPressed, sf::Keyboard::isKeyPressed(state.controls[RIGHT_ROTATION]))) this->rotate('R');
	else if (keyPressed(this->leftRotateKeyPressed, sf::Keyboard::isKeyPressed(state.controls[LEFT_ROTATION]))) this->rotate('L');

	if (keyPressed(this->instantDescentKeyPressed, sf::Keyboard::isKeyPressed(state.controls[INSTANT_DESCENT])))
	{
		this->replace_cases(this->posToDelete, CURRENT_BLOCK, EMPTY);
		this->m_hitablePoints = this->get_ghost_pos();
		this->actualize_tetr_position();
		this->landing();
	}

	if (keyPressed(this->holdKeyPressed, sf::Keyboard::isKeyPressed(state.controls[HOLD]) && can_use_hold)) this->use_hold();

	this->display_grid(window);
	this->display_tetr_to_come(window);
	this->display_hold(window);
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::replace_cases(std::array<sf::Vector2i, 4>& positions, char casetype_to_replace, char replacing_case)
{
	for (char i = 0; i < positions.size(); i++)
		if (this->grid[positions[i].y][positions[i].x] == casetype_to_replace)  this->grid[positions[i].y][positions[i].x] = replacing_case;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::actualize_tetr_position()
{
	// Empty the actual ghost
	this->replace_cases(this->ghost, GHOST, EMPTY);

	// Create the new ghost at the new position
	this->ghost = this->get_ghost_pos();
	this->replace_cases(this->ghost, EMPTY, GHOST);

	// Move the current tetromino to the good position
	for (char i = 0; i < 4; i++) this->grid[this->m_hitablePoints[i].y][this->m_hitablePoints[i].x] = CURRENT_BLOCK;

	this->posToDelete = this->m_hitablePoints;
}

/*--------------------------------------------------------------------------------------------------------*/

char Grid::get_random_tetromino()
{
	char random_tetr;
	bool present = true;

	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<short> distr(0, 6);

	if (this->nb_selected_tetros == this->tetros_selected.size())
	{
		for (unsigned char i = 0; i < this->tetros_selected.size(); i++) this->tetros_selected[i] = EMPTY;

		this->nb_selected_tetros = 0;
	}

	while (present)
	{
		present = false;
		random_tetr = distr(eng);

		unsigned char i = 0;

		while (i < this->tetros_selected.size() && !present)
		{
			if (this->tetros_selected[i] == random_tetr) present = true;
			i++;
		}
	}

	this->tetros_selected[this->nb_selected_tetros] = random_tetr;
	this->nb_selected_tetros++;

	return random_tetr;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::display_grid(sf::RenderWindow& window)
{
	sf::RectangleShape cell(sf::Vector2f(CASE_SIZE - 5, CASE_SIZE - 5));

	// Display the grid
	for (char i = 0; i < GRID_WIDTH; i++)
	{
		for (char j = 0; j < GRID_HEIGHT; j++)
		{
			cell.setPosition(j * CASE_SIZE, i * CASE_SIZE);

			if (this->grid[i][j] == EMPTY)				cell.setFillColor(this->colours[EMPTY]);
			else if (this->grid[i][j] == CURRENT_BLOCK) cell.setFillColor(this->colours[this->tetros_to_come[0]]);
			else if (this->grid[i][j] == GHOST)			cell.setFillColor(this->colours[GHOST]);
			else										cell.setFillColor(this->colours[this->grid[i][j]]);

			window.draw(cell);
		}
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::display_tetr_to_come(sf::RenderWindow& window)
{
	sf::RectangleShape cell(sf::Vector2f(NEXT - 2, NEXT - 2));

	for (unsigned char k = 1; k < 7; k++) // For each tetrominos to come 
	{
		sf::Vector2i corner(3, 0);
		if (this->tetros_to_come[k] == I_SHAPE) corner = sf::Vector2i(3, -1);

		// Create the matrix corresponding to the k tetromino to come
		std::vector<std::vector<char>> matrix_tetr_to_come = pos_to_matrix(set_positions(this->tetros_to_come[k]), this->tetros_to_come[k], corner);
		
		display_matrix
		(
			window,
			matrix_tetr_to_come,
			TETR_TO_COME_X,
			TETR_TO_COME_Y + 3 * k * NEXT,
			cell,
			this->colours[this->tetros_to_come[k]],
			CURRENT_BLOCK
		);
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::display_hold(sf::RenderWindow& window)
{
	sf::RectangleShape cell(sf::Vector2f(NEXT - 2, NEXT - 2));

	if (this->tetros_in_hold != EMPTY)
	{
		sf::Vector2i corner(3, 0);
		if (this->tetros_in_hold == I_SHAPE) corner = sf::Vector2i(3, -1);

		std::vector<std::vector<char>> matrix_held_tetr = pos_to_matrix(set_positions(this->tetros_in_hold), this->tetros_in_hold, corner);

		display_matrix
		(
			window,
			matrix_held_tetr,
			HOLDING_PLACE_X,
			HOLDING_PLACE_Y,
			cell,
			this->colours[this->tetros_in_hold],
			CURRENT_BLOCK
		);
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::set_tetromino(bool for_hold)
{
	if (!for_hold) for (unsigned char i = 0; i < this->tetros_to_come.size() - 1; i++) this->tetros_to_come[i] = this->tetros_to_come[i + 1];

	this->tetros_to_come[this->tetros_to_come.size() - 1] = get_random_tetromino();

	std::array<sf::Vector2i, 4> positions = this->set_positions(this->tetros_to_come[0]);

	for (unsigned char i = 0; i < 4; i++)
	{
		if (this->grid[positions[i].y][positions[i].x] >= I_SHAPE && this->grid[positions[i].y][positions[i].x] <= O_SHAPE)
		{
			this->game_over = true;
		}
	}

	if (!this->game_over)
	{
		this->m_hitablePoints = positions;

		this->posToDelete = this->m_hitablePoints;

		this->leftHandCorner = sf::Vector2i(3, 0);

		if (this->tetros_to_come[0] == I_SHAPE) this->leftHandCorner = sf::Vector2i(3, -1);

		this->set_matrix();

		this->actualize_tetr_position();

		this->tetroSet = true;
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::set_matrix()
{
	char size = this->current_tetros_matrix.size();

	// Reset the actual tetrmino matrix
	for (char i = size - 1; i >= 0; i--)
	{
		for (char j = 0; j < size; j++) this->current_tetros_matrix[i].pop_back();

		this->current_tetros_matrix.pop_back();
	}

	this->current_tetros_matrix = this->pos_to_matrix(this->m_hitablePoints, this->tetros_to_come[0], this->leftHandCorner);
}

/*--------------------------------------------------------------------------------------------------------*/

std::array<sf::Vector2i, 4> Grid::set_positions(char shape)
{
	std::array<sf::Vector2i, 4> positions;

	switch (shape)
	{
	case I_SHAPE:
		return { sf::Vector2i(3,0), sf::Vector2i(4,0), sf::Vector2i(5,0), sf::Vector2i(6,0) };

	case J_SHAPE:
		return { sf::Vector2i(3,0), sf::Vector2i(3,1), sf::Vector2i(4,1), sf::Vector2i(5,1) };

	case L_SHAPE:
		return { sf::Vector2i(5,0), sf::Vector2i(3,1), sf::Vector2i(4,1), sf::Vector2i(5,1) };

	case Z_SHAPE:
		return { sf::Vector2i(3,0), sf::Vector2i(4,0), sf::Vector2i(4,1), sf::Vector2i(5,1) };

	case T_SHAPE:
		return { sf::Vector2i(4,0), sf::Vector2i(3,1), sf::Vector2i(4,1), sf::Vector2i(5,1) };

	case S_SHAPE:
		return { sf::Vector2i(4,0), sf::Vector2i(5,0), sf::Vector2i(3,1), sf::Vector2i(4,1) };

	case O_SHAPE:
		return { sf::Vector2i(4,0), sf::Vector2i(5,0), sf::Vector2i(4,1), sf::Vector2i(5,1) };
	}
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
	this->replace_cases(this->posToDelete, CURRENT_BLOCK, EMPTY);

	for (char i = 0; i < 4; i++)
	{
		coordinates[i].x += x;
		coordinates[i].y += y;
	}

	this->actualize_tetr_position();

	if (coordinates == this->m_hitablePoints)
	{
		this->leftHandCorner.x += x;
		this->leftHandCorner.y += y;
	}
}

/*--------------------------------------------------------------------------------------------------------*/

bool Grid::check_rotate(char side)
{
	if (this->tetros_to_come[0] == O_SHAPE) return false;

	bool can_rotate = true;

	std::vector<std::vector<char>> test_matrix = rotate_matrix(this->current_tetros_matrix, side);

	unsigned char i = 0;

	std::array<sf::Vector2i, 4> positions = this->matrix_to_pos(test_matrix);

	can_rotate = this->check_set_pos(this->matrix_to_pos(test_matrix));

	if (!can_rotate) can_rotate = this->wall_kick(test_matrix);

	return can_rotate;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::rotate(char side)
{
	if (this->check_rotate(side))
	{
		this->replace_cases(this->posToDelete, CURRENT_BLOCK, EMPTY);

		char k = 0;

		this->current_tetros_matrix = rotate_matrix(this->current_tetros_matrix, side);

		this->m_hitablePoints = this->matrix_to_pos(this->current_tetros_matrix);

		this->actualize_tetr_position();
	}
}

/*--------------------------------------------------------------------------------------------------------*/

bool Grid::wall_kick(std::vector<std::vector<char>> test_matrix)
{
	std::array<sf::Vector2i, 4> positions = this->matrix_to_pos(test_matrix);

	if (this->check_next_pos(positions, 1, 0))
	{
		// Move the artificials positions on the right
		this->move_next_pos(positions, 1, 0);

		this->leftHandCorner.x++;

		this->m_hitablePoints = positions;

		return true;
	}

	// The same thing for the left
	else if (this->check_next_pos(positions, -1, 0))
	{
		this->move_next_pos(positions, -1, 0);

		this->leftHandCorner.x--;

		this->m_hitablePoints = positions;

		return true;
	}

	// If a single move right or left is not enough
	else if (this->tetros_to_come[0] == I_SHAPE)
	{
		// Check for the right movement
		this->move_next_pos(positions, 2, 0);

		if (this->check_set_pos(positions))
		{
			this->posToDelete = this->m_hitablePoints;

			this->move_next_pos(this->m_hitablePoints, 2, 0);

			return true;
		}

		// Check for the left movement
		this->move_next_pos(positions, -4, 0);

		if (this->check_set_pos(positions))
		{
			this->posToDelete = this->m_hitablePoints;

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
		unsigned char j = 0;
		bool filled_line = true;

		while (j < GRID_HEIGHT && filled_line)
		{
			if (this->grid[i][j] == EMPTY || this->grid[i][j] == GHOST) filled_line = false;

			j++;
		}

		if (filled_line)
		{
			for (unsigned char j = 0; j < GRID_HEIGHT; j++) this->grid[i][j] = EMPTY;

			for (unsigned char j = i; j > 0; j--) for (unsigned char k = 0; k < GRID_HEIGHT; k++) this->grid[j][k] = this->grid[j - 1][k];
		}
	}
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::landing()
{
	for (char i = 0; i < m_hitablePoints.size(); i++)
		this->grid[this->m_hitablePoints[i].y][this->m_hitablePoints[i].x] = this->tetros_to_come[0];

	this->tetroSet = false;

	this->clear_lines();

	if (!this->can_use_hold) can_use_hold = true;
}

/*--------------------------------------------------------------------------------------------------------*/

bool Grid::check_set_pos(std::array<sf::Vector2i, 4> positions)
{
	for (unsigned char i = 0; i < positions.size(); i++)
	{
		if (positions[i].x < 0 || positions[i].x > 9 ||
			positions[i].y < 0 || positions[i].y > 19 ||
			(this->grid[positions[i].y][positions[i].x] >= I_SHAPE && this->grid[positions[i].y][positions[i].x] <= O_SHAPE))
			return false;
	}

	return true;
}

/*--------------------------------------------------------------------------------------------------------*/

void Grid::use_hold()
{
	this->replace_cases(this->m_hitablePoints, CURRENT_BLOCK, EMPTY);
	this->replace_cases(this->ghost, GHOST, EMPTY);

	if (this->tetros_in_hold == EMPTY)
	{
		this->tetros_in_hold = this->tetros_to_come[0];
		this->set_tetromino(false);
	}
	else
	{
		char temp = this->tetros_to_come[0];
		this->tetros_to_come[0] = this->tetros_in_hold;
		this->tetros_in_hold = temp;
		this->set_tetromino(true);
	}

	this->can_use_hold = false;
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
				pos[k].x = j + this->leftHandCorner.x;
				pos[k].y = i + this->leftHandCorner.y;

				k++;
			}
		}
	}

	return pos;
}

/*--------------------------------------------------------------------------------------------------------*/

std::vector<std::vector<char>> Grid::pos_to_matrix(std::array<sf::Vector2i, 4> pos, char shape, sf::Vector2i corner)
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

	for (unsigned char i = 0; i < 4; i++) matrix[pos[i].y - corner.y][pos[i].x - corner.x] = CURRENT_BLOCK;

	return matrix;
}

/*--------------------------------------------------------------------------------------------------------*/

std::array<sf::Vector2i, 4> Grid::get_ghost_pos()
{
	std::array<sf::Vector2i, 4> positions = this->m_hitablePoints;

	while (this->check_next_pos(positions, 0, 1)) for (unsigned char i = 0; i < 4; i++) positions[i].y++;

	return positions;
}

/*--------------------------------------------------------------------------------------------------------*/