#include "PuzzleSolver.h"


PuzzleSolver::PuzzleSolver() : row(0), column(0), r(-1), c(-1)
{
}


PuzzleSolver::~PuzzleSolver()
{
}


void PuzzleSolver::AddNodesToQueue()
{
	//These variable are for making my function cleaner and not have very long lines of code
	char NodeColor = adjMartix[queueNode.front().first][queueNode.front().second].color;
	int NodeColumn = queueNode.front().second;
	int NodeRow = queueNode.front().first;
	string NodeDirection = adjMartix[queueNode.front().first][queueNode.front().second].direction;
	
	int i, j = 0; //i is the row and j is the column
	
	//This if block takes the direction of the node that we are currently on and finds all nodes of opposite color
	//and adds them to the queue to be explored. As I discover each node it is marked as visted and stores 
	//the locaton of its parent node.
	if (NodeDirection == "N")
	{
		for (i = NodeRow; i >= 0; i--)
		{
			if (adjMartix[i][NodeColumn].color != NodeColor && adjMartix[i][NodeColumn].visited == 0)
			{
				queueNode.push(make_pair(i, NodeColumn));
		
				adjMartix[i][NodeColumn].visited = 1;
				adjMartix[i][NodeColumn].parentNode = make_pair(NodeRow, NodeColumn);
			}
		}
	}
	else if (NodeDirection == "NE")
	{
		for (i = NodeRow, j = NodeColumn; i >= 0 && j < column; i--, j++)
		{
			if (adjMartix[i][j].color != NodeColor && adjMartix[i][j].visited == 0)
			{
				queueNode.push(make_pair(i, j));

				adjMartix[i][j].visited = 1;
				adjMartix[i][j].parentNode = make_pair(NodeRow, NodeColumn);
			}
		}
	}
	else if (NodeDirection == "E")
	{
		for (i = NodeColumn; i < column; i++)
		{
			if (adjMartix[NodeRow][i].color != NodeColor && adjMartix[NodeRow][i].visited == 0)
			{
				queueNode.push(make_pair(NodeRow, i));

				adjMartix[NodeRow][i].visited = 1;
				adjMartix[NodeRow][i].parentNode = make_pair(NodeRow, NodeColumn);
			}
		}
	}
	else if (NodeDirection == "SE")
	{
		for (i = NodeRow, j = NodeColumn; i < row && j < column; i++, j++)
		{
			if (adjMartix[i][j].color != NodeColor && adjMartix[i][j].visited == 0)
			{
				queueNode.push(make_pair(i, j));

				adjMartix[i][j].visited = 1;
				adjMartix[i][j].parentNode = make_pair(NodeRow, NodeColumn);
			}
		}
	}
	else if (NodeDirection == "S")
	{
		for (i = NodeRow; i < row; i++)
		{
			if (adjMartix[i][NodeColumn].color != NodeColor && adjMartix[i][NodeColumn].visited == 0)
			{
				queueNode.push(make_pair(i, NodeColumn));

				adjMartix[i][NodeColumn].visited = 1;
				adjMartix[i][NodeColumn].parentNode = make_pair(NodeRow, NodeColumn);
			}
		}
	}
	else if (NodeDirection == "SW")
	{
		for (i = NodeRow, j = NodeColumn; i < row && j >= 0; i++, j--)
		{
			if (adjMartix[i][j].color != NodeColor && adjMartix[i][j].visited == 0)
			{
				queueNode.push(make_pair(i, j));

				adjMartix[i][j].visited = 1;
				adjMartix[i][j].parentNode = make_pair(NodeRow, NodeColumn);
			}
		}
	}
	else if (NodeDirection == "W")
	{
		for (i = NodeColumn; i >= 0; i--)
		{
			if (adjMartix[NodeRow][i].color != NodeColor && adjMartix[NodeRow][i].visited == 0)
			{
				queueNode.push(make_pair(NodeRow, i));

				adjMartix[NodeRow][i].visited = 1;
				adjMartix[NodeRow][i].parentNode = make_pair(NodeRow, NodeColumn);
			}
		}
	}
	else if(NodeDirection == "NW")
	{
		for (i = NodeRow, j = NodeColumn; i >= 0 && j >= 0; i--, j--)
		{
			if (adjMartix[i][j].color != NodeColor && adjMartix[i][j].visited == 0)
			{
				queueNode.push(make_pair(i, j));

				adjMartix[i][j].visited = 1;
				adjMartix[i][j].parentNode = make_pair(NodeRow, NodeColumn);
			}
		}
	}
}


void PuzzleSolver::CreateMatrix(int r, int c)
{
	//Creates the adjacency matrix
	adjMartix = new Node*[r];
	for (int i = 0; i < r; i++)
	{
		adjMartix[i] = new Node[c];
	}

	
}


void PuzzleSolver::BFS()
{	
	//A BFS search by starting at the upper left corner and traversing the graph by exploring
	//each nodes neighbors untill all have been explored.
	queueNode.push(make_pair(0, 0));
	while (!queueNode.empty())
	{
		adjMartix[queueNode.front().first][queueNode.front().second].visited = 1;
		AddNodesToQueue();
		queueNode.pop();
	}
}


void PuzzleSolver::PrintGraph()
{
	//Prints the graph stored in the matrix for testing
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << adjMartix[i][j].parentNode.first << '-' << adjMartix[i][j].parentNode.second << ' ';
		}
		cout << endl;
	}
}


void PuzzleSolver::PrintPath()
{
	int i = row - 1;
	int j = column - 1;
	int parentRow, parentColumn;
	int tempRow, tempColumn;
	
	//Starts at the goal node and follows back to its parent nodes storing the path untill
	//we reach the start node
	do
	{
		//Holds location of parent node
		parentRow = adjMartix[i][j].parentNode.first;
		parentColumn = adjMartix[i][j].parentNode.second;
		
		//Finds the distance from the parent node
		tempRow = i - adjMartix[i][j].parentNode.first;
		tempColumn = j - adjMartix[i][j].parentNode.second;

		//Stores the direction and distance from the parent node to the node were currently on
		if (adjMartix[parentRow][parentColumn].direction[0] == 'S')
		{
			pathToEnd.push_back(make_pair(adjMartix[parentRow][parentColumn].direction, tempRow));
		}
		else if (adjMartix[parentRow][parentColumn].direction[0] == 'N')
		{
			pathToEnd.push_back(make_pair(adjMartix[parentRow][parentColumn].direction, (tempRow * -1)));
		}
		else if (adjMartix[parentRow][parentColumn].direction == "E")
		{
			pathToEnd.push_back(make_pair(adjMartix[parentRow][parentColumn].direction, tempColumn));
		}
		else if (adjMartix[parentRow][parentColumn].direction == "W")
		{
			pathToEnd.push_back(make_pair(adjMartix[parentRow][parentColumn].direction, tempColumn * -1));
		}

		i = parentRow;
		j = parentColumn;
	} while (i != 0 || j != 0);

	for (int i = pathToEnd.size()-1; i >= 0; i--)
	{
		cout << pathToEnd[i].second << pathToEnd[i].first<< ' ';
	}
	cout << endl;
}


void PuzzleSolver::SetGraph(string data)
{
	string direction;
	column = 0;
	
	for (unsigned int i = 0; i < data.size(); i++) //Parses the data from the file
	{
		//Looks for the next color in the data string
		if (data[i] == 'R' || data[i] == 'B')
		{
			//Creates a node and stores the data
			adjMartix[row][column].color = data[i];
			adjMartix[row][column].visited = 0;
			adjMartix[row][column].parentNode = make_pair(0, 0);
			
			//Stores the direction the node is pointing to
			if (data[i + 3] != ' ')
			{
				adjMartix[row][column].direction = data.substr(i + 2, 2);
				i = i + 3;
			}
			else
			{
				adjMartix[row][column].direction = data.substr(i + 2, 1);
				i = i + 2;
			}
			column++;
		}
		else if (data[i] == 'O') //A special case for the goal node
		{
			adjMartix[row][column].color = 'O';
			adjMartix[row][column].visited = 0;
			adjMartix[row][column].direction = data[i];
			column++;
		}
	}
	
	row++;
}
