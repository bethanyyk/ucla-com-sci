// BOARD MEMBER FUNCTION IMPLEMENTATIONS

#include "Board.h"
#include "Side.h"
#include <vector>
using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole)
{
	m_holes = nHoles;
	if (m_holes < 1)
	{
		m_holes = 1;
	}

	if (nInitialBeansPerHole < 0)
	{
		nInitialBeansPerHole = 0;
	}

	m_nVector.push_back(0);
	m_sVector.push_back(0);
	for (int i = 0; i < nHoles; i++)
	{
		m_nVector.push_back(nInitialBeansPerHole);
		m_sVector.push_back(nInitialBeansPerHole);
	}
}

int Board::holes() const
{
	return m_holes;
}

int Board::beans(Side s, int hole) const
{
	if (hole < 0 || hole > m_holes)
	{
		return -1;
	}

	if (s == NORTH)
	{
		return m_nVector[hole];
	}
	else if (s == SOUTH)
	{
		return m_sVector[hole];
	}
	else
	{
		return -1;
	}
}

int Board::beansInPlay(Side s) const
{
	int total = 0;

	if (s == NORTH)
	{
		for (size_t i = 1; i <= m_holes; i++)
		{
			total += m_nVector[i];
		}
	}
	if (s == SOUTH)
	{
		for (size_t i = 1; i <= m_holes; i++)
		{
			total += m_sVector[i];
		}
	}
	
	return total;
}

int Board::totalBeans() const
{
	int total = 0;

	for (size_t i = 0; i < m_nVector.size(); i++)
	{
		total += m_nVector[i];
	}
	for (size_t i = 0; i < m_sVector.size(); i++)
	{
		total += m_sVector[i];
	}

	return total;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (hole < 1 || hole > m_holes || beans(s, hole) < 1)
	{
		return false;
	}

	Side currentSide = s;
	int currentHole = hole;
	int beansToSow = beans(s, hole);
	setBeans(s, hole, 0);	

	while (beansToSow > 0)
	{
		if (currentSide == NORTH)
		{
			currentHole--;
			if (currentHole < 0)
			{
				currentSide = SOUTH;
				currentHole = 1;
				m_sVector.at(1)++;
			}
			else
			{
				m_nVector.at(currentHole)++;
			}
		}
		else if (currentSide == SOUTH)
		{
			currentHole++;
			if (currentHole > m_holes)
			{
				currentHole = 0;
				m_sVector.at(POT)++;
			}
			else if (currentHole == 1)
			{
				currentSide = NORTH;
				currentHole = m_holes;
				m_nVector.at(currentHole)++;

			}
			else
			{
				m_sVector.at(currentHole)++;
			}
		}
		beansToSow--;
	}

	endSide = currentSide;
	endHole = currentHole;
	return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole < 1 || hole > m_holes)
	{
		return false;
	}

	int beansToMove = 0;
	if (s == NORTH)
	{
		beansToMove = m_nVector[hole];
		m_nVector.at(hole) = 0;
	}
	if (s == SOUTH)
	{
		beansToMove = m_sVector[hole];
		m_sVector.at(hole) = 0;
	}

	if (potOwner == NORTH)
	{
		m_nVector[POT] += beansToMove;
	}
	if (potOwner == SOUTH)
	{
		m_sVector[POT] += beansToMove;
	}

	return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole < 0 || hole > m_holes)
	{
		return false;
	}
	if (beans < 0)
	{
		return false;
	}

	if (s == NORTH)
	{
		m_nVector[hole] = beans;
	}
	if (s == SOUTH)
	{
		m_sVector[hole] = beans;
	}
	return true;
}