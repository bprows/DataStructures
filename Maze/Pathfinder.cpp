#include "Pathfinder.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

const int X_SIZE = 5;
const int Y_SIZE = 5;
const int Z_SIZE = 5;
const int BACKGROUND = 1;
const int WALL = 0;
const int TEMPORARY = 2; // Used to show this path has been explored
const int PATH = 3;

Pathfinder::Pathfinder() {
	srand(time(NULL));
	for (int z = 0; z < Z_SIZE; z++) {
		for (int y = 0; y < Y_SIZE; y++) {
			for (int x = 0; x < X_SIZE; x++) {
				maze_grid[x][y][z] = 1;
			}
		}
	}
}

// helper function
void Pathfinder::copy_maze() {
	for (int z = 0; z < Z_SIZE; z++) {
		for (int y = 0; y < Y_SIZE; y++) {
			for (int x = 0; x < X_SIZE; x++) {
				maze_grid[x][y][z] = tmp_grid[x][y][z];
			}
		}
	}
}

bool Pathfinder::importMaze(string file_name) {

	cout << "importMaze from " << file_name << endl;
	ifstream file (file_name.c_str());
	if (file.is_open()) {
	    string line;
		int x_count = 0;
		for (int z = 0; z < Z_SIZE; z++) {
			
		    for (int y = 0; y < Y_SIZE; y++) {
		        getline(file, line);

		         // if line is not new line
		        if (line == "") {
		        	getline(file, line);
		        }

		        stringstream ss(line);

	        	for (int x = 0; x < X_SIZE; x++) {
	            	string tmp;
	            	int value;
	            	ss >> tmp;
	            	if (tmp == "0" || tmp == "1") {
	                	value = atoi(tmp.c_str());
	                	tmp_grid[x][y][z] = value;    
	            	}
	            	else {
	            		 return false; // if something other than 1 or 0
	            	}
	            
	        	}
	    	}
	    	if (z < Z_SIZE - 1 && file.eof()) {
	    		return false;
	    	}
		}
		if (!file.eof()) {
			return false;
		}
	}
	else {
		return false;
	}
	// check valid space in start and finish.
	if (tmp_grid[0][0][0] != BACKGROUND || tmp_grid[X_SIZE - 1][Y_SIZE - 1][Z_SIZE - 1] != BACKGROUND) {
	    return false;
	}
	copy_maze();
    return true;
}

string Pathfinder::toString() const {
	// we know that maze_grid is valid
	string s;
	
	for (int z = 0; z < Z_SIZE; z++) {
		for (int y = 0; y < Y_SIZE; y++) {
			for (int x = 0; x < X_SIZE; x++) {
				if (x == 0) {
					s += to_string(maze_grid[x][y][z]);
				}
				else {
					s += " " + to_string(maze_grid[x][y][z]);
				}
			}
			s += "\n";
		}
		if (z < 4) {
			s += "\n";	
		}
	}
	return s;
}

bool Pathfinder::find_maze_path(int grid[X_SIZE][Y_SIZE][Z_SIZE], int x, int y, int z) {
	
	solution.push_back("("+to_string(x)+", "+to_string(y)+", "+to_string(z)+")");
	
	if (x < 0 || y < 0 || z < 0 || x >= X_SIZE || y >= Y_SIZE || z >= Z_SIZE) {
		solution.pop_back();
		return false;
	}     // Cell is out of bounds.
	
	else if (grid[x][y][z] != BACKGROUND) {
		solution.pop_back();
		return false;
	}     // Cell is on barrier or dead end.
	
	else if (x == X_SIZE - 1 && y == Y_SIZE - 1 && z == Z_SIZE - 1) {
	    grid[x][y][z] = PATH;         // Cell is on path
		return true;               // and is maze exit.
	}
	else { 
	    // Recursive case.
	    // Attempt to find a path from each neighbor.
	    // Tentatively mark cell as on path.
		grid[x][y][z] = PATH;
	    if	(	find_maze_path(grid, x - 1, y, z) // left
	        	|| find_maze_path(grid, x + 1, y, z) // Right
	        	|| find_maze_path(grid, x, y - 1, z) // Down
	        	|| find_maze_path(grid, x, y + 1, z) // up
	        	|| find_maze_path(grid, x, y, z - 1) // backward
	        	|| find_maze_path(grid, x, y, z + 1)) { // forward
	    	return true;
	    }
	    else {
	    	grid[x][y][z] = TEMPORARY;  // Dead end.
	    	solution.pop_back();
	    	return false;
		}
	}
}

vector<string> Pathfinder::solveMaze() {
	for (int z = 0; z < Z_SIZE; z++) {
		for (int y = 0; y < Y_SIZE; y++) {
			for (int x = 0; x < X_SIZE; x++) {
				tmp_grid[x][y][z] = maze_grid[x][y][z];
			}
		}
	}
	solution.clear();
	find_maze_path(tmp_grid, 0,0,0);
    return solution;
}

void Pathfinder::createRandomMaze() {
	for (int z = 0; z < Z_SIZE; z++) {
		for (int y = 0; y < Y_SIZE; y++) {
			for (int x = 0; x < X_SIZE; x++) {
				maze_grid[x][y][z] = rand() % 2;
			}
		}
	}
}