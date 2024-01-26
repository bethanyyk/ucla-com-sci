// GAME MEMBER FUNCTION IMPLEMENTATIONS

#include "Game.h"
#include "Side.h"
#include <string>
#include <iostream>
using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
	:m_board(b), m_south(south), m_north(north), currentTurn(south)
{
	
}

void Game::display() const
{
	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << " ";
	}
	cout << m_north->name() << endl;

	cout << "  ";
	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << m_board.beans(NORTH, i) << "  ";
	}
	cout << endl;

	cout << m_board.beans(NORTH, POT);
	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << "   ";
	}
	cout << m_board.beans(SOUTH, POT);
	cout << endl;

	cout << "  ";
	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << m_board.beans(SOUTH, i) << "  ";
	}
	cout << endl;

	for (int i = 1; i <= m_board.holes(); i++)
	{
		cout << " ";
	}
	cout << m_south->name() << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& Winner) const
{
	if (m_board.beansInPlay(NORTH) == 0)
	{
		over = true;

		if (beans(NORTH, POT) < beans(SOUTH, POT) + m_board.beansInPlay(SOUTH))
		{
			hasWinner = true;
			Winner = SOUTH;
		}
		else if (beans(NORTH, POT) > beans(SOUTH, POT) + m_board.beansInPlay(SOUTH))
		{
			hasWinner = true;
			Winner = NORTH;
		}
		else
		{
			hasWinner = false;
		}
	}
	else if (m_board.beansInPlay(SOUTH) == 0)
	{
		over = true;

		if (beans(SOUTH, POT) < beans(NORTH, POT) + m_board.beansInPlay(NORTH))
		{
			hasWinner = true;
			Winner = NORTH;
		}
		else if (beans(SOUTH, POT) > beans(NORTH, POT) + m_board.beansInPlay(NORTH))
		{
			hasWinner = true;
			Winner = SOUTH;
		}
		else
		{
			hasWinner = false;
		}
	}
	else
	{
		over = false;
	}
}

bool Game::move(Side s)
{
	display();
	if (s == NORTH && m_board.beansInPlay(NORTH) == 0)
	{
		cout << "There are no valid moves that " << m_north->name() << " can make." << endl;
		int opponentBeans = m_board.beans(SOUTH, POT) + m_board.beansInPlay(SOUTH);
		m_board.setBeans(SOUTH, POT, opponentBeans);
		for (int i = 1; i <= m_board.holes(); i++)
		{
			m_board.setBeans(SOUTH, i, 0);
		}
		display();
		return false;
	}
	else if (s == SOUTH && m_board.beansInPlay(SOUTH) == 0)
	{
		cout << "There are no valid moves that " << m_south->name() << " can make." << endl;
		int sBeans = m_board.beans(NORTH, POT) + m_board.beansInPlay(NORTH);
		m_board.setBeans(NORTH, POT, sBeans);
		for (int i = 1; i <= m_board.holes(); i++)
		{
			m_board.setBeans(NORTH, i, 0);
		}
		display();
		return false;
	}

	Side eS;
	int eH;
	if (s == SOUTH)
	{
		int sH = m_south->chooseMove(m_board, SOUTH);
		m_board.sow(SOUTH, sH, eS, eH);
		display();
		if (eS == SOUTH && eH == POT)
		{
			cout << m_south->name() << " should make another move." << endl;
			move(SOUTH);
		}
		if (eS == SOUTH && eH != POT && beans(SOUTH, eH) == 1 && beans(NORTH, eH) > 0)
		{
			cout << m_south->name() << " made a successful capture." << endl;
			m_board.moveToPot(SOUTH, eH, SOUTH);
			m_board.moveToPot(NORTH, eH, SOUTH);
			display();
		}
	}
	if (s == NORTH)
	{
		int sH = m_north->chooseMove(m_board, NORTH);
		m_board.sow(NORTH, sH, eS, eH);
		display();
		// Check if the last bean ended up in the player's pot
		if (eS == NORTH && eH == POT)
		{ 
			cout << m_north->name() << " should make another move." << endl;
			move(NORTH);
		}
		// Check if there was a capture
		if (eS == NORTH && eH != POT && beans(NORTH, eH) == 1 && beans(SOUTH, eH) > 0)
		{
			cout << m_north->name() << " made a successful capture." << endl;
			m_board.moveToPot(NORTH, eH, NORTH);
			m_board.moveToPot(SOUTH, eH, NORTH);
			display();
		}
	}
	return true;
}

void Game::play()
{
	bool over;
	bool hasWinner;
	Side winner;
	status(over, hasWinner, winner);

	while (!over)
	{
		cout << "It is " << m_south->name() << "'s turn to make a move." << endl;
		move(SOUTH);
		if (!m_north->isInteractive() && !m_south->isInteractive())
		{
			cout << "Press ENTER to continue" << endl;
			cin.ignore(10000, '\n');
		}
		cout << "It is " << m_north->name() << "'s turn to make a move." << endl;
		move(NORTH);
		if (!m_north->isInteractive() && !m_south->isInteractive())
		{
			cout << "Press ENTER to continue" << endl;
			cin.ignore(10000, '\n');
		}
		status(over, hasWinner, winner);
	}

	cout << "Winner: ";
	if (winner == NORTH)
	{
		cout << m_north->name();
	}
	else
	{
		cout << m_south->name();
	}
}

int Game::beans(Side s, int hole) const
{
	return m_board.beans(s, hole);
}