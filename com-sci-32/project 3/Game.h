// GAME CLASS DEFINITION

#ifndef GAME_H
#define GAME_H

#include "Side.h"
#include "Board.h"
#include "Player.h"

class Game
{
public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& Winner) const;
	bool move(Side s);
	void play();
	int beans(Side s, int hole) const;
private:
	Board m_board;
	Player* m_north;
	Player* m_south;

	Player* currentTurn;
};

#endif