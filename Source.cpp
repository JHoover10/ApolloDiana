#include "PuzzleSolver.h"

#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	PuzzleSolver Puzzle;

	ifstream myFile(argv[1]);
	int row, column;
	string Input;
	
	//Gets the size of the puzzle
	myFile >> row >> column;
	Puzzle.CreateMatrix(row, column);
	getline(myFile, Input);
	
	//Takes in the points of the puzzle and stores them
	//into the graph
	while (getline(myFile, Input))
	{
		Puzzle.SetGraph(Input);
	}
	
	Puzzle.BFS(); //Finds the shortest path from start to finish using BFS search
	
	Puzzle.PrintPath(); //Prints the path of the shortest path from start to finish
	
	return 1;
}
