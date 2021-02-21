#include <iostream>
#include <queue>
using namespace std;

int AlgorithmChoice;				//Pick the type of algorithm
int CheckPlace = 0;					//Variable to use for Misplaced Tile.
int Match_Tile_To_Goal = 0;			//Variable to check if current tile is the same as the goal puzzle.
int heuristic = 0;					//h(n) = heuristic
int nodesSearched = 0;				//Variable to check how many nodes are searched at the end.
int total_cost = 0;					//f(n) = g(n) + h(n)
int depth = 0;						//Variable to check the depth level at the end.
int temp1 = 0;						//Used to swap the tiles
int temp2 = 0;						//Used to swap the tiles

//Got from online forum on how to put a 2D array into a queue:(https://www.daniweb.com/programming/software-development/threads/315334/how-to-put-a-2-dimensional-array-in-a-queue)
//Specifically from username 'mayyubiradar'
struct PuzzleSolver
{
	//Matrix Puzzle;
	int PuzzleState[3][3];			//Used as current puzzle when traveling each node in queue
	int total_cost;					//f(n) = addition between g(n) and h(n)
	int nodeDepth;					//g(n) = depth
	//Default constructor needed because I overwritten constructor
	PuzzleSolver()
	{

	}
	//Overwritten constructor
	PuzzleSolver(int total_cost_A_Star, int nodeDepth_A_Star):total_cost(total_cost_A_Star), nodeDepth(nodeDepth_A_Star)
	{
	}
};

//This function is to force the priority queue to order the total cost from low to high
//Got the overload function from the link:(https://www.daniweb.com/programming/software-development/threads/315334/how-to-put-a-2-dimensional-array-in-a-queue)
bool operator<(PuzzleSolver const& Puzzle1, PuzzleSolver const& Puzzle2)
{
	return Puzzle1.total_cost > Puzzle2.total_cost;
}

queue<PuzzleSolver>Queue_Tiles;						//Queue to store the states(for Uniform Cost Search)
priority_queue<PuzzleSolver>PrioQueue_Tiles;		//Priority queue to stores states(for both A* searches)

//This will be used to compare the current puzzle state and see if both match.
int PuzzleTileGoal[3][3] = {{1,2,3},
							{4,5,6},
							{7,8,0}};

//This returns the heuristic for the Misplaced Tiles
int Return_Check_Place(PuzzleSolver PuzzleCheckPlace)
{
	int CheckPlace = 0;
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (PuzzleCheckPlace.PuzzleState[i][j] == PuzzleTileGoal[i][j])
			{
				CheckPlace++;
			}
		}
	}
	//For Loop for checking what is misplaced in the second row
	for (int i = 1; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (PuzzleCheckPlace.PuzzleState[i][j] == PuzzleTileGoal[i][j])
			{
				CheckPlace++;
			}
		}
	}
	//For Loop for checking what is misplaced in the first row
	for (int i = 2; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (PuzzleCheckPlace.PuzzleState[i][j] == PuzzleTileGoal[i][j])
			{
				CheckPlace++;
			}
		}
	}
	heuristic = 8 - CheckPlace;
	return heuristic;
}

//This returns the heuristic for the Manhattan Distance
int Return_Man_Heuristic(PuzzleSolver Puzzle_Man)
{
//Looking at Top Left Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[0][0] == 2)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][0] == 3)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][0] == 4)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][0] == 5)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][0] == 6)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][0] == 7)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][0] == 8)
	{
		heuristic = heuristic + 3;
	}
//Looking at Top Middle Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[0][1] == 1)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][1] == 3)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][1] == 4)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][1] == 5)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][1] == 6)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][1] == 7)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][1] == 8)
	{
		heuristic = heuristic + 2;
	}
//Looking at Top Right Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[0][2] == 1)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][2] == 2)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][2] == 4)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][2] == 5)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][2] == 6)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][2] == 7)
	{
		heuristic = heuristic + 4;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[0][2] == 8)
	{
		heuristic = heuristic + 3;
	}
//Looking at Middle Left Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[1][0] == 1)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][0] == 2)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][0] == 3)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][0] == 5)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][0] == 6)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][0] == 7)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][0] == 8)
	{
		heuristic = heuristic + 2;
	}
//Looking at Center Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[1][1] == 1)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][1] == 2)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][1] == 3)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][1] == 4)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][1] == 6)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][1] == 7)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][1] == 8)
	{
		heuristic = heuristic + 1;
	}
//Looking at Middle Right Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[1][2] == 1)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][2] == 2)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][2] == 3)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][2] == 4)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][2] == 5)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][2] == 7)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[1][2] == 8)
	{
		heuristic = heuristic + 2;
	}
//Looking at Bottom Left Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[2][0] == 1)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][0] == 2)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][0] == 3)
	{
		heuristic = heuristic + 4;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][0] == 4)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][0] == 5)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][0] == 6)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][0] == 8)
	{
		heuristic = heuristic + 1;
	}
//Looking at Bottom Middle Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[2][1] == 1)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][1] == 2)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][1] == 3)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][1] == 4)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][1] == 5)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][1] == 6)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][1] == 7)
	{
		heuristic = heuristic + 1;
	}
//Looking at Bottom Left Tile(Manhattan)
	if (PrioQueue_Tiles.top().PuzzleState[2][2] == 1)
	{
		heuristic = heuristic + 4;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 2)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 3)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 4)
	{
		heuristic = heuristic + 3;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 5)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 6)
	{
		heuristic = heuristic + 1;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 7)
	{
		heuristic = heuristic + 2;
	}
	else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 8)
	{
		heuristic = heuristic + 1;
	}
	return heuristic;
}

//When the current puzzle state is equal to the goal state, then we finish for the Uniform Cost
void Success_Node(PuzzleSolver FinishedProblem)
{
	cout << "To solve this problem, the search algorithm expanded a total of " << nodesSearched << endl;
	cout << "The maximum number of nodes inside of the queue is: " << Queue_Tiles.size() << endl;
	cout << "The depth of the goal node is " << Queue_Tiles.front().nodeDepth << endl;
}

//When the current puzzle state is equal to the goal state, then we finish, but for both A* searches.
void Success_Node_A_Star(PuzzleSolver FinishedProblem)
{
	cout << "To solve this problem, the search algorithm expanded a total of " << nodesSearched << endl;
	cout << "The maximum number of nodes inside of the queue is: " << PrioQueue_Tiles.size() << endl;
	cout << "The depth of the goal node is " << PrioQueue_Tiles.top().nodeDepth << endl;
}

//Starting the Uniform Cost Implementation
void UniformCost(PuzzleSolver Puzzle_Uni_Cost)
{
	//These instances of PuzzleSolver are useful when creating the children
	PuzzleSolver PuzzleHolder1;
	PuzzleSolver PuzzleHolder2;
	PuzzleSolver PuzzleHolder3;
	PuzzleSolver PuzzleHolder4;

	cout << '\n' << "Expanding the starting state: " << '\n';
	for (int i = 0; i < 3; i++)				//Check for the inital puzzle(default or the made puzzle)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << Puzzle_Uni_Cost.PuzzleState[i][j] << '\t';
		}
		cout << "\n";
	}
	Queue_Tiles.push(Puzzle_Uni_Cost);		//Push initial struct into queue
	cout << '\n';
	while (1)											//Infinite Loop
	{
		//Set each PuzzleSolver instance the front of the current node in the list
		PuzzleHolder1 = Queue_Tiles.front();
		PuzzleHolder2 = Queue_Tiles.front();
		PuzzleHolder3 = Queue_Tiles.front();
		PuzzleHolder4 = Queue_Tiles.front();
		if (Queue_Tiles.empty())						//If queue is empty, then we did not find the solution anywhere
		{
			return void("Failure!"); 					//return failure
		}
		cout << "Printing out the front of the Queue with h(n) = " << heuristic <<  " and g(n) = " << Queue_Tiles.front().nodeDepth << endl;
		nodesSearched++;
		for (int i = 0; i < 3; i++)											//For loop for printing front of the queue
		{
			for (int j = 0; j < 3; j++)
			{
				cout << Queue_Tiles.front().PuzzleState[i][j] << '\t';
			}
			cout << "\n";
		}
		for (int i = 0; i < 3; i++)														//For loop to match current puzzle with goal puzzle
		{
			for (int j = 0; j < 3; j++)
			{
				if (Queue_Tiles.front().PuzzleState[i][j] == PuzzleTileGoal[i][j])
				{
					Match_Tile_To_Goal++;
				}
			}
			cout << "\n";
		}
		if (Match_Tile_To_Goal == 9)													//If every tile in current puzzle matches with every space in the goal puzzle, then we are done!
		{
			Success_Node(Queue_Tiles.front());
			break;
		}
		Match_Tile_To_Goal = 0;

		//The following if/else statements are for the certain position of the blank space
		if (Queue_Tiles.front().PuzzleState[0][0] == 0)					//If '0' is at top left, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][0];					//These two temp values will be used to swap out tiles. This will be used for the rest of the search algorithms
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[0][0] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][0];
			temp2 = PuzzleHolder2.PuzzleState[0][1];
			PuzzleHolder2.PuzzleState[0][0] = temp2;
			PuzzleHolder2.PuzzleState[0][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder2);
		}
		else if (Queue_Tiles.front().PuzzleState[0][1] == 0)			//If '0' is at top middle, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][1];
			temp2 = PuzzleHolder1.PuzzleState[0][0];
			PuzzleHolder1.PuzzleState[0][1] = temp2;
			PuzzleHolder1.PuzzleState[0][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][1];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[0][1] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[0][1];
			temp2 = PuzzleHolder3.PuzzleState[0][2];
			PuzzleHolder3.PuzzleState[0][1] = temp2;
			PuzzleHolder3.PuzzleState[0][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder3);
		}
		else if (Queue_Tiles.front().PuzzleState[0][2] == 0)			//If '0' is at top right, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][2];
			temp2 = PuzzleHolder1.PuzzleState[0][1];
			PuzzleHolder1.PuzzleState[0][2] = temp2;
			PuzzleHolder1.PuzzleState[0][1] = temp1;
			PuzzleHolder1.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][2];
			temp2 = PuzzleHolder2.PuzzleState[1][2];
			PuzzleHolder2.PuzzleState[0][2] = temp2;
			PuzzleHolder2.PuzzleState[1][2] = temp1;
			PuzzleHolder2.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder2);
		}
		else if (Queue_Tiles.front().PuzzleState[1][0] == 0)			//If '0' is at middle left, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][0];
			temp2 = PuzzleHolder1.PuzzleState[0][0];
			PuzzleHolder1.PuzzleState[1][0] = temp2;
			PuzzleHolder1.PuzzleState[0][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][0];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[1][0] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][0];
			temp2 = PuzzleHolder3.PuzzleState[2][0];
			PuzzleHolder3.PuzzleState[1][0] = temp2;
			PuzzleHolder3.PuzzleState[2][0] = temp1;
			PuzzleHolder3.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder3);
		}
		else if (Queue_Tiles.front().PuzzleState[1][1] == 0)			//If '0' is center, then 4 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][1];
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[1][1] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][1];
			temp2 = PuzzleHolder2.PuzzleState[0][1];
			PuzzleHolder2.PuzzleState[1][1] = temp2;
			PuzzleHolder2.PuzzleState[0][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][1];
			temp2 = PuzzleHolder3.PuzzleState[1][2];
			PuzzleHolder3.PuzzleState[1][1] = temp2;
			PuzzleHolder3.PuzzleState[1][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder3);
			temp1 = PuzzleHolder4.PuzzleState[1][1];
			temp2 = PuzzleHolder4.PuzzleState[2][1];
			PuzzleHolder4.PuzzleState[1][1] = temp2;
			PuzzleHolder4.PuzzleState[2][1] = temp1;
			PuzzleHolder4.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder4);
		}
		else if (Queue_Tiles.front().PuzzleState[1][2] == 0)			//If '0' is at middle right, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][2];
			temp2 = PuzzleHolder1.PuzzleState[0][2];
			PuzzleHolder1.PuzzleState[1][2] = temp2;
			PuzzleHolder1.PuzzleState[0][2] = temp1;
			PuzzleHolder1.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][2];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[1][2] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][2];
			temp2 = PuzzleHolder3.PuzzleState[2][2];
			PuzzleHolder3.PuzzleState[1][2] = temp2;
			PuzzleHolder3.PuzzleState[2][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder3);
		}
		else if (Queue_Tiles.front().PuzzleState[2][0] == 0)			//If '0' is at bottom left, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[2][0];
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[2][0] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[2][0];
			temp2 = PuzzleHolder2.PuzzleState[2][1];
			PuzzleHolder2.PuzzleState[2][0] = temp2;
			PuzzleHolder2.PuzzleState[2][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder2);
		}
		else if (Queue_Tiles.front().PuzzleState[2][1] == 0)			//If '0' is at bottom middle, then 3 children
		{
			PuzzleHolder1.nodeDepth++;
			temp1 = PuzzleHolder1.PuzzleState[2][1];
			temp2 = PuzzleHolder1.PuzzleState[2][0];
			PuzzleHolder1.PuzzleState[2][1] = temp2;
			PuzzleHolder1.PuzzleState[2][0] = temp1;
			Queue_Tiles.push(PuzzleHolder1);
			PuzzleHolder2.nodeDepth++;
			temp1 = PuzzleHolder2.PuzzleState[2][1];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[2][1] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			Queue_Tiles.push(PuzzleHolder2);
			PuzzleHolder3.nodeDepth++;
			temp1 = PuzzleHolder3.PuzzleState[2][1];
			temp2 = PuzzleHolder3.PuzzleState[2][2];
			PuzzleHolder3.PuzzleState[2][1] = temp2;
			PuzzleHolder3.PuzzleState[2][2] = temp1;
			Queue_Tiles.push(PuzzleHolder3);
		}
		else if (Queue_Tiles.front().PuzzleState[2][2] == 0)			//If '0' is at bottom right, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[2][2];
			temp2 = PuzzleHolder1.PuzzleState[2][1];
			PuzzleHolder1.PuzzleState[2][2] = temp2;
			PuzzleHolder1.PuzzleState[2][1] = temp1;
			PuzzleHolder1.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[2][2];
			temp2 = PuzzleHolder2.PuzzleState[1][2];
			PuzzleHolder2.PuzzleState[2][2] = temp2;
			PuzzleHolder2.PuzzleState[1][2] = temp1;
			PuzzleHolder2.nodeDepth++;
			Queue_Tiles.push(PuzzleHolder2);
		}
		Queue_Tiles.pop();													//Pop front of the queue after checking if queue is empty(like in Alg.)
		cout << "Length of queue is now: " << Queue_Tiles.size() << endl;
	}
}
//Starting the A* with Misplace Heuristic Implementation
void A_Star_Misplaced(PuzzleSolver Puzzle_A_Star_Misplaced)
{
	//These instances of PuzzleSolver are useful when creating the children
	PuzzleSolver PuzzleHolder1;
	PuzzleSolver PuzzleHolder2;
	PuzzleSolver PuzzleHolder3;
	PuzzleSolver PuzzleHolder4;

	cout << '\n' << "Expanding the starting state: " << '\n';
	for (int i = 0; i < 3; i++)				//Check for the inital puzzle(default or the made puzzle)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << Puzzle_A_Star_Misplaced.PuzzleState[i][j] << '\t';
		}
		cout << "\n";
	}
	PrioQueue_Tiles.push(Puzzle_A_Star_Misplaced);		//Push initial struct into queue
	cout << '\n';

	while (1)											//Infinite Loop
	{
		//Set each PuzzleSolver instance the front of the current node in the list
		PuzzleHolder1 = PrioQueue_Tiles.top();
		PuzzleHolder2 = PrioQueue_Tiles.top();
		PuzzleHolder3 = PrioQueue_Tiles.top();
		PuzzleHolder4 = PrioQueue_Tiles.top();
		if (PrioQueue_Tiles.empty())						//If queue is empty, then we did not find the solution anywhere
		{
			return void("Failure!"); 						//return failure
		}
		nodesSearched++;
		Return_Check_Place(PrioQueue_Tiles.top());
		cout << "Printing out the front of the Queue with h(n) = " << heuristic << " and g(n) = " << PrioQueue_Tiles.top().nodeDepth << endl;
		PuzzleSolver Hold_Total_Cost;										//This is to hold the current top node, since Priority queue doenst allow to change top of node
		Hold_Total_Cost = PrioQueue_Tiles.top();
		Hold_Total_Cost.total_cost = heuristic + PrioQueue_Tiles.top().nodeDepth;			//f(n) = h(n) + g(n)
		cout << "The total cost comes out to be: " << Hold_Total_Cost.total_cost << endl;
		heuristic = 0;
		for (int i = 0; i < 3; i++)											//For loop for printing front of the queue
		{
			for (int j = 0; j < 3; j++)
			{
				cout << PrioQueue_Tiles.top().PuzzleState[i][j] << '\t';
			}
			cout << "\n";
		}
		for (int i = 0; i < 3; i++)											//For loop to match current puzzle with goal puzzle
		{
			for (int j = 0; j < 3; j++)
			{
				if (PrioQueue_Tiles.top().PuzzleState[i][j] == PuzzleTileGoal[i][j])
				{
					Match_Tile_To_Goal++;
				}
			}
			cout << "\n";
		}
		if (Match_Tile_To_Goal == 9)													//If every tile in current puzzle matches with every space in the goal puzzle, then we are done!
		{
			Success_Node_A_Star(PrioQueue_Tiles.top());
			break;
		}
		Match_Tile_To_Goal = 0;
		nodesSearched++;
		CheckPlace = 0;
		//The following if/else statements are for the certain position of the blank space
		if (PrioQueue_Tiles.top().PuzzleState[0][0] == 0)					//If '0' is at top left, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][0];						
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[0][0] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;	//Calculating total cost for certain child. The same thing is calculated for Manhattan
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][0];
			temp2 = PuzzleHolder2.PuzzleState[0][1];
			PuzzleHolder2.PuzzleState[0][0] = temp2;
			PuzzleHolder2.PuzzleState[0][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;	
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[0][1] == 0)			//If '0' is at top middle, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][1];
			temp2 = PuzzleHolder1.PuzzleState[0][0];
			PuzzleHolder1.PuzzleState[0][1] = temp2;
			PuzzleHolder1.PuzzleState[0][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][1];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[0][1] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[0][1];
			temp2 = PuzzleHolder3.PuzzleState[0][2];
			PuzzleHolder3.PuzzleState[0][1] = temp2;
			PuzzleHolder3.PuzzleState[0][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Check_Place(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[0][2] == 0)			//If '0' is at top right, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][2];
			temp2 = PuzzleHolder1.PuzzleState[0][1];
			PuzzleHolder1.PuzzleState[0][2] = temp2;
			PuzzleHolder1.PuzzleState[0][1] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][2];
			temp2 = PuzzleHolder2.PuzzleState[1][2];
			PuzzleHolder2.PuzzleState[0][2] = temp2;
			PuzzleHolder2.PuzzleState[1][2] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[1][0] == 0)			//If '0' is at middle left, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][0];
			temp2 = PuzzleHolder1.PuzzleState[0][0];
			PuzzleHolder1.PuzzleState[1][0] = temp2;
			PuzzleHolder1.PuzzleState[0][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][0];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[1][0] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][0];
			temp2 = PuzzleHolder3.PuzzleState[2][0];
			PuzzleHolder3.PuzzleState[1][0] = temp2;
			PuzzleHolder3.PuzzleState[2][0] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Check_Place(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[1][1] == 0)			//If '0' is center, then 4 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][1];
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[1][1] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][1];
			temp2 = PuzzleHolder2.PuzzleState[0][1];
			PuzzleHolder2.PuzzleState[1][1] = temp2;
			PuzzleHolder2.PuzzleState[0][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][1];
			temp2 = PuzzleHolder3.PuzzleState[1][2];
			PuzzleHolder3.PuzzleState[1][1] = temp2;
			PuzzleHolder3.PuzzleState[1][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Check_Place(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
			temp1 = PuzzleHolder4.PuzzleState[1][1];
			temp2 = PuzzleHolder4.PuzzleState[2][1];
			PuzzleHolder4.PuzzleState[1][1] = temp2;
			PuzzleHolder4.PuzzleState[2][1] = temp1;
			PuzzleHolder4.nodeDepth++;
			Return_Check_Place(PuzzleHolder4);
			PuzzleHolder4.total_cost = PuzzleHolder4.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder4);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[1][2] == 0)			//If '0' is at middle right, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][2];
			temp2 = PuzzleHolder1.PuzzleState[0][2];
			PuzzleHolder1.PuzzleState[1][2] = temp2;
			PuzzleHolder1.PuzzleState[0][2] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][2];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[1][2] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][2];
			temp2 = PuzzleHolder3.PuzzleState[2][2];
			PuzzleHolder3.PuzzleState[1][2] = temp2;
			PuzzleHolder3.PuzzleState[2][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Check_Place(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[2][0] == 0)			//If '0' is at bottom left, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[2][0];
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[2][0] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[2][0];
			temp2 = PuzzleHolder2.PuzzleState[2][1];
			PuzzleHolder2.PuzzleState[2][0] = temp2;
			PuzzleHolder2.PuzzleState[2][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[2][1] == 0)			//If '0' is at bottom middle, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[2][1];
			temp2 = PuzzleHolder1.PuzzleState[2][0];
			PuzzleHolder1.PuzzleState[2][1] = temp2;
			PuzzleHolder1.PuzzleState[2][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[2][1];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[2][1] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[2][1];
			temp2 = PuzzleHolder3.PuzzleState[2][2];
			PuzzleHolder3.PuzzleState[2][1] = temp2;
			PuzzleHolder3.PuzzleState[2][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Check_Place(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 0)			//If '0' is at bottom right, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[2][2];
			temp2 = PuzzleHolder1.PuzzleState[2][1];
			PuzzleHolder1.PuzzleState[2][2] = temp2;
			PuzzleHolder1.PuzzleState[2][1] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Check_Place(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[2][2];
			temp2 = PuzzleHolder2.PuzzleState[1][2];
			PuzzleHolder2.PuzzleState[2][2] = temp2;
			PuzzleHolder2.PuzzleState[1][2] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Check_Place(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
		}
		heuristic = 0;
		CheckPlace = 0;
		cout << "Length of queue is now: " << PrioQueue_Tiles.size() << endl;
		PrioQueue_Tiles.pop();												//Pop front of the queue after checking if queue is empty(like in Alg.)
	}
}
//Starting the A* with Manhattan Heuristic Implementation
void A_Star_Manhattan(PuzzleSolver Puzzle_A_Star_ManHat)
{
	//These instances of PuzzleSolver are useful when creating the children
	PuzzleSolver PuzzleHolder1;
	PuzzleSolver PuzzleHolder2;
	PuzzleSolver PuzzleHolder3;
	PuzzleSolver PuzzleHolder4;

	cout << '\n' << "Expanding the starting state: " << '\n';
	for (int i = 0; i < 3; i++)				//Check for the inital puzzle(default or the made puzzle)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << Puzzle_A_Star_ManHat.PuzzleState[i][j] << '\t';
		}
		cout << "\n";
	}
	PrioQueue_Tiles.push(Puzzle_A_Star_ManHat);		//Push initial struct into queue
	cout << '\n';

	while (1)											//Infinite Loop
	{
		//Set each PuzzleSolver instance the front of the current node in the list
		PuzzleHolder1 = PrioQueue_Tiles.top();
		PuzzleHolder2 = PrioQueue_Tiles.top();
		PuzzleHolder3 = PrioQueue_Tiles.top();
		PuzzleHolder4 = PrioQueue_Tiles.top();
		if (PrioQueue_Tiles.empty())						//If queue is empty, then we did not find the solution anywhere
		{
			return void("Failure!"); 					//return failure
		}
		nodesSearched++;								//Increased the number of nodes that are searched
		Return_Man_Heuristic(PrioQueue_Tiles.top());
		cout << "Printing out the front of the Queue with h(n) = " << heuristic << " and g(n) = " << PrioQueue_Tiles.top().nodeDepth << endl;
		PuzzleSolver Hold_Total_Cost;										//This is to hold the current top node, since Priority queue doenst allow to change top of node
		Hold_Total_Cost = PrioQueue_Tiles.top();
		Hold_Total_Cost.total_cost = heuristic + PrioQueue_Tiles.top().nodeDepth;			//f(n) = h(n) + g(n)
		cout << "The total cost comes out to be: " << Hold_Total_Cost.total_cost << endl;
		heuristic = 0;
		for (int i = 0; i < 3; i++)											//For loop for printing front of the queue
		{
			for (int j = 0; j < 3; j++)
			{
				cout << PrioQueue_Tiles.top().PuzzleState[i][j] << '\t';
			}
			cout << "\n";
		}
		for (int i = 0; i < 3; i++)											//For loop to match current puzzle with goal puzzle
		{
			for (int j = 0; j < 3; j++)
			{
				if (PrioQueue_Tiles.top().PuzzleState[i][j] == PuzzleTileGoal[i][j])
				{
					CheckPlace++;
				}
			}
		}
		if (CheckPlace == 9)													//If every tile in current puzzle matches with every space in the goal puzzle, then we are done!
		{
			Success_Node_A_Star(PrioQueue_Tiles.top());
			break;
		}
		CheckPlace = 0;
		//The following if/else statements are for the certain position of the blank space
		if (PrioQueue_Tiles.top().PuzzleState[0][0] == 0)					//If '0' is at top left, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][0];
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[0][0] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][0];
			temp2 = PuzzleHolder2.PuzzleState[0][1];
			PuzzleHolder2.PuzzleState[0][0] = temp2;
			PuzzleHolder2.PuzzleState[0][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[0][1] == 0)			//If '0' is at top middle, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][1];
			temp2 = PuzzleHolder1.PuzzleState[0][0];
			PuzzleHolder1.PuzzleState[0][1] = temp2;
			PuzzleHolder1.PuzzleState[0][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][1];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[0][1] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[0][1];
			temp2 = PuzzleHolder3.PuzzleState[0][2];
			PuzzleHolder3.PuzzleState[0][1] = temp2;
			PuzzleHolder3.PuzzleState[0][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[0][2] == 0)			//If '0' is at top right, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[0][2];
			temp2 = PuzzleHolder1.PuzzleState[0][1];
			PuzzleHolder1.PuzzleState[0][2] = temp2;
			PuzzleHolder1.PuzzleState[0][1] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[0][2];
			temp2 = PuzzleHolder2.PuzzleState[1][2];
			PuzzleHolder2.PuzzleState[0][2] = temp2;
			PuzzleHolder2.PuzzleState[1][2] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[1][0] == 0)			//If '0' is at middle left, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][0];
			temp2 = PuzzleHolder1.PuzzleState[0][0];
			PuzzleHolder1.PuzzleState[1][0] = temp2;
			PuzzleHolder1.PuzzleState[0][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][0];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[1][0] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][0];
			temp2 = PuzzleHolder3.PuzzleState[2][0];
			PuzzleHolder3.PuzzleState[1][0] = temp2;
			PuzzleHolder3.PuzzleState[2][0] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[1][1] == 0)			//If '0' is center, then 4 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][1];
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[1][1] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][1];
			temp2 = PuzzleHolder2.PuzzleState[0][1];
			PuzzleHolder2.PuzzleState[1][1] = temp2;
			PuzzleHolder2.PuzzleState[0][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][1];
			temp2 = PuzzleHolder3.PuzzleState[1][2];
			PuzzleHolder3.PuzzleState[1][1] = temp2;
			PuzzleHolder3.PuzzleState[1][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
			temp1 = PuzzleHolder4.PuzzleState[1][1];
			temp2 = PuzzleHolder4.PuzzleState[2][1];
			PuzzleHolder4.PuzzleState[1][1] = temp2;
			PuzzleHolder4.PuzzleState[2][1] = temp1;
			PuzzleHolder4.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder4);
			PuzzleHolder4.total_cost = PuzzleHolder4.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder4);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[1][2] == 0)			//If '0' is at middle right, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[1][2];
			temp2 = PuzzleHolder1.PuzzleState[0][2];
			PuzzleHolder1.PuzzleState[1][2] = temp2;
			PuzzleHolder1.PuzzleState[0][2] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[1][2];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[1][2] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[1][2];
			temp2 = PuzzleHolder3.PuzzleState[2][2];
			PuzzleHolder3.PuzzleState[1][2] = temp2;
			PuzzleHolder3.PuzzleState[2][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[2][0] == 0)			//If '0' is at bottom left, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[2][0];
			temp2 = PuzzleHolder1.PuzzleState[1][0];
			PuzzleHolder1.PuzzleState[2][0] = temp2;
			PuzzleHolder1.PuzzleState[1][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[2][0];
			temp2 = PuzzleHolder2.PuzzleState[2][1];
			PuzzleHolder2.PuzzleState[2][0] = temp2;
			PuzzleHolder2.PuzzleState[2][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[2][1] == 0)			//If '0' is at bottom middle, then 3 children
		{
			temp1 = PuzzleHolder1.PuzzleState[2][1];
			temp2 = PuzzleHolder1.PuzzleState[2][0];
			PuzzleHolder1.PuzzleState[2][1] = temp2;
			PuzzleHolder1.PuzzleState[2][0] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[2][1];
			temp2 = PuzzleHolder2.PuzzleState[1][1];
			PuzzleHolder2.PuzzleState[2][1] = temp2;
			PuzzleHolder2.PuzzleState[1][1] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
			temp1 = PuzzleHolder3.PuzzleState[2][1];
			temp2 = PuzzleHolder3.PuzzleState[2][2];
			PuzzleHolder3.PuzzleState[2][1] = temp2;
			PuzzleHolder3.PuzzleState[2][2] = temp1;
			PuzzleHolder3.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder3);
			PuzzleHolder3.total_cost = PuzzleHolder3.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder3);
		}
		else if (PrioQueue_Tiles.top().PuzzleState[2][2] == 0)			//If '0' is at bottom right, then 2 children
		{
			temp1 = PuzzleHolder1.PuzzleState[2][2];
			temp2 = PuzzleHolder1.PuzzleState[2][1];
			PuzzleHolder1.PuzzleState[2][2] = temp2;
			PuzzleHolder1.PuzzleState[2][1] = temp1;
			PuzzleHolder1.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder1);
			PuzzleHolder1.total_cost = PuzzleHolder1.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder1);
			temp1 = PuzzleHolder2.PuzzleState[2][2];
			temp2 = PuzzleHolder2.PuzzleState[1][2];
			PuzzleHolder2.PuzzleState[2][2] = temp2;
			PuzzleHolder2.PuzzleState[1][2] = temp1;
			PuzzleHolder2.nodeDepth++;
			Return_Man_Heuristic(PuzzleHolder2);
			PuzzleHolder2.total_cost = PuzzleHolder2.nodeDepth + heuristic;
			heuristic = 0;
			PrioQueue_Tiles.push(PuzzleHolder2);
		}
		cout << "Length of queue is now: " << PrioQueue_Tiles.size() << endl;
		PrioQueue_Tiles.pop();												//Pop front of the queue after checking if queue is empty(like in Alg.)
	}
}

void DefaultPuzzle()
{
	//Create an instance of the struct, named "PuzzleDefault"
	PuzzleSolver PuzzleDefault;
	//PuzzleSolver_A_Star PuzzleDefault_A_Star;
	PuzzleDefault.PuzzleState[0][0] = 1;
	PuzzleDefault.PuzzleState[0][1] = 2;
	PuzzleDefault.PuzzleState[0][2] = 3;
	PuzzleDefault.PuzzleState[1][0] = 4;
	PuzzleDefault.PuzzleState[1][1] = 0;
	PuzzleDefault.PuzzleState[1][2] = 6;
	PuzzleDefault.PuzzleState[2][0] = 7;
	PuzzleDefault.PuzzleState[2][1] = 5;
	PuzzleDefault.PuzzleState[2][2] = 8;
	//Initialize all of the other struct data to 0
	PuzzleDefault.total_cost = 0;
	PuzzleDefault.nodeDepth = 0;
	//Choosing an Algorithm to solve the problem
	cout << "Choose an Algorithm: " << endl;
	cout << '\t' << "1. Uniform Cost Search" << endl;
	cout << '\t' << "2. A* with Misplaced Tile Heuristic" << endl;
	cout << '\t' << "3. A* with Manhattan Distance Heuristic" << endl;
	cin >> AlgorithmChoice;
	if (AlgorithmChoice == 1)
	{
		cout << "You have chosen the Uniform Cost Search" << endl;
		UniformCost(PuzzleDefault);
	}
	else if (AlgorithmChoice == 2)
	{
		cout << "You have chosen the A* with Misplaced Tile Heuristic" << endl;
		A_Star_Misplaced(PuzzleDefault);
	}
	else if (AlgorithmChoice == 3)
	{
		cout << "You have chosen the A* with Manhattan Distance Heuristic" << endl;
		A_Star_Manhattan(PuzzleDefault);
	}
	else
	{
		cout << "You have entered an invalid input" << endl;
	}
}

void PuzzleMaker()
{
	//Create an instance of the struct, named "PuzzleEnter"
	PuzzleSolver PuzzleEnter;
	//Initialize all of the other struct data to 0
	PuzzleEnter.total_cost = 0;
	PuzzleEnter.nodeDepth = 0;
	//PuzzleEnter.heuristic = 0;
	cout << "Enter in your puzzle, where using '0' represents the blank space " << endl;
	cout << '\t' << "Enter the first row(Use only three numbers), use spaces or tabs between numbers: ";
	//For Loop for entering the first row into the array
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> PuzzleEnter.PuzzleState[i][j];
		}
	}
	cout << '\t' << "Enter the second row(Use only three numbers), use spaces or tabs between numbers: ";
	//For Loop for entering the second row into the array
	for (int i = 1; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> PuzzleEnter.PuzzleState[i][j];
		}
	}
	cout << '\t' << "Enter the third row(Use only three numbers), use spaces or tabs between numbers: ";
	//For Loop for entering the third row into the array
	for (int i = 2; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cin >> PuzzleEnter.PuzzleState[i][j];
		}
	}
	//Choosing an Algorithm to solve the problem
	cout << "Choose an Algorithm: " << endl;
	cout << '\t' << "1. Uniform Cost Search" << endl;
	cout << '\t' << "2. A* with Misplaced Tile Heuristic" << endl;
	cout << '\t' << "3. A* with Manhattan Distance Heuristic" << endl;
	cin >> AlgorithmChoice;
	if (AlgorithmChoice == 1)
	{
		cout << "You have chosen the Uniform Cost Search" << endl;
		UniformCost(PuzzleEnter);
	}
	else if (AlgorithmChoice == 2)
	{
		cout << "You have chosen the A* with Misplaced Tile Heuristic" << endl;
		A_Star_Misplaced(PuzzleEnter);
	}
	else if (AlgorithmChoice == 3)
	{
		cout << "You have chosen the A* with Manhattan Distance Heuristic" << endl;
		A_Star_Manhattan(PuzzleEnter);
	}
	else
	{
		cout << "You have entered an invalid input" << endl;
	}
}

int main()
{
	int makeChoice;		//Choose default or make your own puzzle
	cout << "Welcome to the Jimmy Le's 8-Puzzle Solver" << endl;
	cout << "Type '1' to use a default puzzle. or '2' to enter your own puzzle." << endl;
	cin >> makeChoice;
	if (makeChoice == 1)
	{
		DefaultPuzzle();
	}
	else if (makeChoice == 2)
	{
		PuzzleMaker();
	}
	else
	{
		cout << "You have entered an invalid input" << endl;
	}
	return 0;
}