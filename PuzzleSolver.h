#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class PuzzleSolver
{
public:
	PuzzleSolver(); //Default constructor
	~PuzzleSolver(); //Default descrtuctor
	void AddNodesToQueue(); //Adds all the neighbors of the current node in the BFS search
	void CreateMatrix(int r, int c); //Creates the adjacency matrix for the graph
	void BFS(); //Performs the BFS on the graph
	void PrintGraph(); //Prints the graph for testing input from file
	void PrintPath(); //Prints the shortest path found by BFS
	void SetGraph(string data); //Takes the data from the file and stores it on the matrix
private:
	struct Node //Holds the info for each node for when we perform our BFS
	{
		char color;
		string direction;
		int visited;
		pair <int, int> parentNode;
	};

	int row, column;
	int r, c;
	Node** adjMartix;
	queue<pair <int, int> > queueNode; //Queue for BFS
	vector <pair <string, int> > pathToEnd; //Holds the shortest path to the goal
};

