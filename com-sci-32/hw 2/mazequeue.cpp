#include <queue>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
{
    // Push the starting coordinate(sr, sc) onto the coordinate stack and update maze[sr][sc] to indicate that the algorithm has encountered it
    // (i.e., set maze[sr][sc] to have a value other than '.')
    queue<Coord> coordQueue;
    Coord start = Coord(sr, sc);
    coordQueue.push(start);
    maze[sr][sc] = '*';

    // While the stack is not empty,
    while (!coordQueue.empty())
    {
        // Pop the top coordinate off the stack.This gives you the current (r,c) location that your algorithm is exploring.
        Coord current = coordQueue.front();
        coordQueue.pop();

        // If the current(r,c) coordinate is equal to the ending coordinate, then we've solved the maze so return true!
        if (current.r() == er && current.c() == ec)
        {
            return true;
        }

        // Check each place you can move from the current cell as follows:
            // If you can move SOUTH and haven't encountered that cell yet,
            // then push the coordinate(r + 1,c) onto the stack and update maze[r + 1][c] to indicate the algorithm has encountered it.
        if (maze[current.r() + 1][current.c()] == '.')
        {
            Coord cur = Coord(current.r() + 1, current.c());
            coordQueue.push(cur);
            maze[current.r() + 1][current.c()] = '*';
        }

        // If you can move EAST and haven't encountered that cell yet,
        // then push the coordinate(r,c + 1) onto the stack and update maze[r][c + 1] to indicate the algorithm has encountered it.
        if (maze[current.r()][current.c() + 1] == '.')
        {
            Coord cur = Coord(current.r(), current.c() + 1);
            coordQueue.push(cur);
            maze[current.r()][current.c() + 1] = '*';
        }

        // If you can move NORTH and haven't encountered that cell yet,
        // then push the coordinate(r - 1,c) onto the stack and update maze[r - 1][c] to indicate the algorithm has encountered it.
        if (maze[current.r() + 1][current.c()] == '.')
        {
            Coord cur = Coord(current.r() - 1, current.c());
            coordQueue.push(cur);
            maze[current.r() - 1][current.c()] = '*';
        }

        // If you can move WEST and haven't encountered that cell yet,
        // then push the coordinate(r,c - 1) onto the stack and update maze[r][c - 1] to indicate the algorithm has encountered it.
        if (maze[current.r()][current.c() - 1] == '.')
        {
            Coord cur = Coord(current.r(), current.c() - 1);
            coordQueue.push(cur);
            maze[current.r()][current.c() - 1] = '*';
        }
    }

    // There was no solution, so return false
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','.','.','X' },
        { 'X','.','.','X','X','.','X','X','.','X' },
        { 'X','.','X','.','.','.','.','X','X','X' },
        { 'X','X','X','X','.','X','X','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','.','.','X','.','X','.','.','.','X' },
        { 'X','X','.','X','.','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3, 4, 8, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}