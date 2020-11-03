#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>

using namespace std;

/* moved to .txt file
vector<vector<int> > board = {{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0}};
*/

enum class State {kNothing, kObstacle, kClosed, kPath};

// function to compare f values of nodes
bool Compare(vector<int> a, vector<int> b)
{
    int f1 = a[2] + a[3];
    int f2 = b[2] + b[3];
    return f1 > f2;
}

// function to sort the cells
void CellSort(vector<vector<int> > *v)
{
    sort(v->begin(), v->end(), Compare); //-> deferences the pointer
}

// Heuristic function to determine how far away a point is from the finish
int Heuristic(int x_1, int x_2, int y_1, int y_2)
{
    return (abs(x_2 - x_1) + abs(y_2 - y_1));
}

// function to check that neighboring node is on the grid and not an obstacle
bool CheckValidCell(int x, int y, vector<vector<State> > &grid)
{
    // check that x is on the grid
    bool on_grid_x = (x >= 0 && x < grid.size());

    // check that y is on the grid
    bool on_grid_y = (y >= 0 && y < grid[0].size());

    // if both x & y are on the grid, set that node to kNothing
    if(on_grid_x && on_grid_y)
    {
        return grid[x][y] == State::kNothing;
    }
    return false;
}

// function to add nodes to the open vector
void AddToOpen(int x, int y, int g, int h, vector<vector<int> > &open_list, vector<vector<State> > &grid)
{
    // add the node to the open_list vector
    open_list.push_back(vector<int>{x, y, g, h});

    // close that node so it doesn't get added again
    grid[x][y] = State::kClosed;
}

// parse through each line of the .txt file
vector<State> ParseLine(string &line)
{
    // make each line into a string
    istringstream i_line(line);

    // declare variables
    int n; char c; vector<State> p_vector;

    // while the line is structure int then char and the char is (comma), push the line into the p_vector
    while(i_line >> n >> c && c == ',')
    {
        // now uses enum to set the 1's equal to State::kObstacle and the 0's each to kNothing
        if(n == 1)
        {
            p_vector.push_back(State::kObstacle);
        }else
        {
            p_vector.push_back(State::kNothing);
        }
        
    }

    return p_vector;

}

// print the contents from the .txt file
vector<vector<State> >ReadBoardFile(string &file)
{
    // string variable for the each lin & vector<vector<int>> var for the board
    string line;
    vector<vector<State> > parsed_vector;

    // ifstream to take in the .txt file
    ifstream the_board(file);

    // if to make sure fstream worked; push_back each line into the parsed vector
    if(the_board)
    {
        while(getline(the_board, line))
        {
            // push each p_vector from ParseLine into the parsed_vector 
            parsed_vector.push_back(ParseLine(line));
        }
    }

    return parsed_vector;
}

// function to determing what to pring based on enum State
string CellString(State &cell)
{
    if(cell == State::kObstacle)
    {
        return "⛰️   ";
    }else
    {
        return "0 ";
    }
    
}

// print the board to the console
void PrintTheBoard(vector<vector<State> > &v)
{
    for(vector<State> i : v)
    {
        for(State j : i)
        {
            cout << CellString(j);
        }
        cout << endl;
    }
}

// search function to search through board and return the solution
vector<vector<State> > Search(vector<vector<State> > &grid, int start[2], int end[2])
{
    // create the vector of open nodes & set starting node information
    vector<vector<int> > open_list{};
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x, y, end[0], end[1]);
    AddToOpen(x, y, g, h, open_list, grid);
    cout << "Oh no, there isn't a path to the end" << endl;
    return vector<vector<State> > {};
}

// main function
int main()
{
    int start[2] = {0, 0};
    int end[2] = {4, 5};
    string path = "./examplemaze.txt";
    vector<vector<State> > board = ReadBoardFile(path);
    auto solution_path = Search(board, start, end);
    PrintTheBoard(solution_path);
}

