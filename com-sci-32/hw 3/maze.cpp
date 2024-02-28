bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	// If the start location is equal to the ending location, then we've
	// solved the maze, so return true.
	if (sr == er && sc == ec) // BASE CASE
	{
		return true;
	}

	// Mark the start location as visted.
	maze[sr][sc] = '*';

	//For each of the four directions,
	// If the location one step in that direction(from the start
		// location) has no wall and is unvisited,
	// then call pathExists starting from that location(and
			// ending at the same ending location as in the
			// current call).
		// If that returned true,
			// then return true.
	
	if (maze[sr - 1][sc] == '.') // North
	{
		if (pathExists(maze, sr - 1, sc, er, ec))
		{
			return true;
		}
	}

	if (maze[sr + 1][sc] == '.') // South
	{
		if (pathExists(maze, sr + 1, sc, er, ec))
		{
			return true;
		}
	}

	if (maze[sr][sc - 1] == '.') // West
	{
		if (pathExists(maze, sr, sc - 1, er, ec))
		{
			return true;
		}
	}

	if (maze[sr][sc + 1] == '.') // East
	{
		if (pathExists(maze, sr + 1, sc, er, ec))
		{
			return true;
		}
	}

	// Return false
	return false;
}

/*#include <iostream>
using namespace std;

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

	return 0;
}*/