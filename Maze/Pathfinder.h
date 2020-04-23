#include "PathfinderInterface.h"

using namespace std;

class Pathfinder: public PathfinderInterface
{
public:
	Pathfinder();
	~Pathfinder() {}

	//Part 1-----------------------------------------------------------------------------------
	/*
	* toString
	*
	* Returns a string representation of the current maze. Returns a maze of all 1s if no maze
	* has yet been generated or imported.
	*
	* A valid string representation of a maze consists only of 125 1s and 0s (each separated
	* by spaces) arranged in five 5x5 grids (each separated by newlines) with no trailing newline. A valid maze must
	* also have 1s in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).
	*
	* Cell (0, 0, 0) is represented by the first number in the string representation of the
	* maze. Increasing in x means moving toward the east, meaning cell (1, 0, 0) is the second
	* number. Increasing in y means moving toward the south, meaning cell (0, 1, 0) is the
	* sixth number. Increasing in z means moving downward to a new grid, meaning cell
	* (0, 0, 1) is the twenty-sixth cell in the maze. Cell (4, 4, 4) is represented by the last number.
	*
	* Returns:		string
	*				A single string representing the current maze
	*/
	string toString() const;
	
	//Part 2-----------------------------------------------------------------------------------
	/*
	* importMaze
	*
	* Reads in a maze from a file with the given file name and stores it as the current maze.
	* Does nothing if the file does not exist or if the file's data does not represent a valid
	* maze.
	*
	* The file's contents must be of the format described above to be considered valid.
	*
	* Parameter:	file_name
	*				The name of the file containing a maze
	* Returns:		bool
	*				True if the maze is imported correctly; false otherwise
	*/
    
    bool importMaze(string file_name);
    
    //bool find_path(int grid[X_SIZE][Y_SIZE][Z_SIZE], int x int y, int z);
    
    vector<string> solveMaze();
    
    void createRandomMaze();
    
    void copy_maze();
    
    bool find_maze_path(int grid[5][5][5], int x, int y, int z);
    
    void init_maze();

	
protected:
    int maze_grid[5][5][5]; // To hold values, set to blank maze
    int tmp_grid[5][5][5]; // for import maze function
    vector<string> solution;
};