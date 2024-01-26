// PLAYER CLASS DEFINITION (AND HUMANPLAYER, BADPLAYER, SMARTPLAYER)

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Side.h"
#include "Board.h"

class Player
{
public:
	Player(std::string name);
	std::string name() const;
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const = 0;
	virtual ~Player();
private:
	std::string m_name;
};

class HumanPlayer :public Player
{
public:
	HumanPlayer(std::string name);
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~HumanPlayer();
};

class BadPlayer :public Player
{
public:
	BadPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~BadPlayer();
};

class SmartPlayer : public Player
{
public:
	SmartPlayer(std::string name);
	virtual int chooseMove(const Board& b, Side s) const;
	virtual ~SmartPlayer();
private:
	int evaluate(const Board& b) const;
	bool completeMove(Board& b, Side s, int hole, Side& endSide, int& endHole) const;
	void minimax(const Board& b, Side s, int& bestMove, int& value, int depth, double timeLimit, const Timer& timer) const;
};

#endif