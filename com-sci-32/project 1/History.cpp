#include <iostream>
#include <string>
using namespace std;

#include "History.h"

History::History(int nRows, int nCols)
	: m_rows(nRows), m_columns(nCols)
{
	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_columns; c++)
		{
			m_grid[r][c] = '.';
		}
	}
}

bool History::record(int r, int c)
{
	if (r < 1 || r > m_rows || c < 1 || c > m_columns)
	{
		return false;
	}
	else
	{
		if (m_grid[r-1][c-1] == '.')
		{
			m_grid[r-1][c-1] = 'A';
		}
		else if (m_grid[r-1][c-1] == 'Z')
		{
			m_grid[r-1][c-1] = 'Z';
		}
		else
		{
			m_grid[r-1][c-1]++;
		}
		return true;
	}
}

void History::display() const
{
	clearScreen();

	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_columns; c++)
		{
			cout << m_grid[r][c];
		}
		cout << endl;
	}
	cout << endl;
}