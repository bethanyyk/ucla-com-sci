// PLAYER MEMBER FUNCTION IMPLEMENTATIONS (AND HUMANPLAYER, BADPLAYER, SMARTPLAYER)

#include "Player.h"
#include "Game.h"
#include <string>
#include <iostream>
#include <limits>
using namespace std;

Player::Player(string name)
{
	m_name = name;
}

string Player::name() const
{
	return m_name;
}

bool Player::isInteractive() const
{
	return false;
}


Player::~Player()
{

}

HumanPlayer::HumanPlayer(string name)
	:Player(name)
{

}

bool HumanPlayer::isInteractive() const
{
	return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	int choice = -1;
	while (choice < 1 || choice > b.holes() || b.beans(s, choice) == 0)
	{
		cout << "Choose a hole to make your move: ";
		cin >> choice;
		cin.ignore(10000, '\n');
	}

	return choice;
}

HumanPlayer::~HumanPlayer()
{

}

BadPlayer::BadPlayer(string name)
	:Player(name)
{

}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) != 0)
		{
			return i;
		}
	}

	return -1;
}

BadPlayer::~BadPlayer()
{

}

SmartPlayer::SmartPlayer(string name)
	:Player(name)
{

}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	int bestMove;
	int value;
	int depth = 0;
	Timer timer;

	minimax(b, s, bestMove, value, depth, 5000.0, timer);
	return bestMove;
}

SmartPlayer::~SmartPlayer()
{

}

int SmartPlayer::evaluate(const Board& b) const
{
	// Check if the game is over
	if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH))
	{
		// Determine the winner or a tie
		if (b.beans(SOUTH, POT) > b.beans(NORTH, POT))
		{
			return INT_MAX; // SOUTH wins
		}
		else if (b.beans(NORTH, POT) > b.beans(SOUTH, POT))
		{
			return INT_MIN; // NORTH wins
		}
		else
		{
			return 0; // Tie
		}
	}

	return b.beans(SOUTH, POT) - b.beans(opponent(NORTH), POT);
	// Since the function gives high numbers to positions that are good for South,
	// then South will try to get into positions that evaluate to high numbers,
	// while North will try to move into positions rated low by the same function
	// (since bad for South is good for North).
}

bool SmartPlayer::completeMove(Board& b, Side s, int hole, Side& eS, int& eH) const
{
	if (hole < 1 || hole > b.holes() || b.beans(s, hole) == 0)
	{
		return false; // Invalid move
	}

	b.sow(s, hole, eS, eH);
	if (eH == POT)
	{
		return false; // Take another turn
	}
	else
	{
		if (eS == s && b.beans(s, eH) == 1 && b.beans(opponent(s), eH) > 0)
		{
			b.moveToPot(opponent(s), eH, s);
			b.moveToPot(s, eH, s);
		}
		return true;
	}
}

void SmartPlayer::minimax(const Board& b, Side s, int& bestMove, int& value, int depth, double timeLimit, const Timer& timer) const
{
	if (b.beansInPlay(s) == 0 || timer.elapsed() > 4.99)
	{
		// Base case: If the game is over or the maximum depth is reached,
		//			  return the evaluation of the current position
		bestMove = -1;
		value = evaluate(b);
		return;
	}

	int start = -1;
	for (int i = 1; i <= b.holes(); i++)
	{
		if (b.beans(s, i) != 0) // Valid move
		{
			start = i;
			break;
		}
	}
	if (start == -1)
	{
		bestMove = -1;
		value = evaluate(b);
		return;
	}

	bestMove = start;
	for (int i = start; i <= b.holes(); i++)
	{
		if (b.beans(s, i) == 0) // Not a valid move
		{
			continue;
		}

		Board temp = b; // Create a copy of board to simulate the move
		Side eS;
		int eH;
		int subtreeValue;
		int opponent_eH;
		int extraTurn_eH;

		if (completeMove(temp, s, i, eS, eH)) // If s completes it's move
		{
			// Recursive call for opponent's turn
			minimax(temp, opponent(s), opponent_eH, subtreeValue, depth + 1, timeLimit, timer);
		}
		else
		{
			// Recursive call for extra turn
			minimax(temp, s, extraTurn_eH, subtreeValue, depth + 1, timeLimit, timer);
		}

		if (i == start) // If the hole 1 was the best hole
		{
			// Update the bestMove and its corresponding value
			// Ensures that bestMove and value are properly assigned before further comparisons and evaluations
			bestMove = i;
			value = subtreeValue;
		}
		if (s == SOUTH && subtreeValue > value)
		{
			value = subtreeValue;
			bestMove = i;
		}
		else if (s == NORTH && subtreeValue < value)
		{
			value = subtreeValue;
			bestMove = i;
		}
	}
}