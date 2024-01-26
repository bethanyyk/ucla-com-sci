#include <iostream>
#include <string>

#ifndef Player_h
#define Player_h

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

    // Mutators
    std::string dropPoisonedCarrot();
    std::string move(int dir);
    void   setDead();

private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

bool recommendMove(const Arena& a, int r, int c, int& bestDir);
int computeDanger(const Arena& a, int r, int c);

#endif