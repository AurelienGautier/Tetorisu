#include "headers/global.hpp"

void displayingText(sf::RenderWindow &window, std::string textToDisplay, sf::Font &font, int size, int positionX, int positionY)
{
    sf::Text thingToDisplay(textToDisplay, font, size);
    thingToDisplay.setPosition(positionX, positionY);
    window.draw(thingToDisplay);
}

/*--------------------------------------------------------------------------------------------------------------*/

// Permet d'éviter les appuis maintenus
bool keyPressed(bool &keyPressed, const bool keyPressedSF)
{
    if(keyPressed)
    {
        if(!keyPressedSF)
        {
            keyPressed = false;
        }
    }
    else if(keyPressedSF)
    {
        keyPressed = true;
        return true;
    }

    return false;
}

/*--------------------------------------------------------------------------------------------------------------*/

std::vector<std::vector<char>> copy_matrix(std::vector<std::vector<char>> matrix)
{
	std::vector<std::vector<char>> result;

	for (int i = 0; i < matrix.size(); i++)	result.push_back(matrix[i]);

	return result;
}

/*--------------------------------------------------------------------------------------------------------------*/

std::vector<std::vector<char>> rotate_matrix(std::vector<std::vector<char>> matrix, char side)
{
	std::vector<std::vector<char>> resultat = copy_matrix(matrix);

	std::vector<int> positions;

	int x = 0;
	int y = 0;

	// Copie les éléments de la matrice dans le tableau à une dimension
	for (int i = 0; i < matrix.size() * matrix[0].size(); i++)
	{
		if (x >= matrix[0].size())
		{
			x = 0;
			y++;
		}

		positions.push_back(matrix[y][x]);

		x++;
	}

	// Tourne la matrice
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			if (side == 'R') resultat[i][j] = positions[(matrix.size() - 1) * matrix.size() - matrix.size() * j + i];
			else resultat[i][j] = positions[(matrix.size() - 1) + matrix.size() * j - i];
		}
	}

	return resultat;
}

/*--------------------------------------------------------------------------------------------------------*/

void display_matrix(sf::RenderWindow& window,
					std::vector<std::vector<char>>& matrix,
					short pos_x,
					short pos_y,
					sf::RectangleShape& cell, sf::Color color,
					unsigned char case_to_display)
{
	for (unsigned char i = 0; i < matrix.size(); i++)
	{
		for (unsigned char j = 0; j < matrix.size(); j++)
		{
			if (matrix[i][j] == case_to_display)
			{
				cell.setPosition(pos_x + NEXT * j, pos_y + NEXT * i);
				cell.setFillColor(color);

				window.draw(cell);
			}
		}
	}
}

/*--------------------------------------------------------------------------------------------------------*/