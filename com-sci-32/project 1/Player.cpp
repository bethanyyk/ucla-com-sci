#include <iostream>
#include <string>
using namespace std;

#include "Player.h"
#include "Arena.h"

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::dropPoisonedCarrot()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned carrot at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned carrot has been dropped.";
}

string Player::move(int dir)
{
    if (attemptMove(*m_arena, dir, m_row, m_col))
    {
        if (m_arena->numberOfRabbitsAt(m_row, m_col) > 0)
        {
            setDead();
            return "Player walked into a rabbit and died.";
        }
        string msg = "Player moved ";
        switch (dir)
        {
        case NORTH: msg += "north"; break;
        case EAST:  msg += "east";  break;
        case SOUTH: msg += "south"; break;
        case WEST:  msg += "west";  break;
        }
        msg += ".";
        return msg;
    }
    else
        return "Player couldn't move; player stands.";
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poisoned carrot and
// not move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // How dangerous is it to stand?
    int standDanger = computeDanger(a, r, c);

    // if it's not safe, see if moving is safer
    if (standDanger > 0)
    {
        int bestMoveDanger = standDanger;
        int bestMoveDir = NORTH;  // arbitrary initialization

        // check the four directions to see if any move is
        // better than standing, and if so, record the best
        for (int dir = 0; dir < NUMDIRS; dir++)
        {
            int rnew = r;
            int cnew = c;
            if (attemptMove(a, dir, rnew, cnew))
            {
                int danger = computeDanger(a, rnew, cnew);
                if (danger < bestMoveDanger)
                {
                    bestMoveDanger = danger;
                    bestMoveDir = dir;
                }
            }
        }

        // if moving is better than standing, recommend move
        if (bestMoveDanger < standDanger)
        {
            bestDir = bestMoveDir;
            return true;
        }
    }
    return false;  // recommend standing
}

int computeDanger(const Arena& a, int r, int c)
{
    // Our measure of danger will be the number of rabbits that might move
    // to position (r,c).  If a rabbit is at that position, it is fatal,
    // so a large value is returned.

    if (a.numberOfRabbitsAt(r, c) > 0)
        return MAXRABBITS + 1;

    int danger = 0;
    if (r > 1)
        danger += a.numberOfRabbitsAt(r - 1, c);
    if (r < a.rows())
        danger += a.numberOfRabbitsAt(r + 1, c);
    if (c > 1)
        danger += a.numberOfRabbitsAt(r, c - 1);
    if (c < a.cols())
        danger += a.numberOfRabbitsAt(r, c + 1);

    return danger;
}