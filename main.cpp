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

// enum class to track our path
enum class State {kNothing, kObstacle, kClosed, kPath, kStart, kFinish};

// 2D array to set the directions you can go from current node
const int delta[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

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
int Heuristic(int x_1, int y_1, int x_2, int y_2)
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
vector<State> ParseLine(string line)
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
string CellString(State cell)
{
    // switch statement to set the path, start, finish, and obstacles
    switch(cell){
        case State::kObstacle: return " ⛰️ ";
        case State::kPath: return " 🚗 ";
        case State::kStart: return " 🚦 ";
        case State::kFinish: return " 🏁 ";
        default: return "  0 ";
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

// expand neighbors functions to try out surrounding nodes
void ExpandNeighbors(const vector<int> &c_node, vector<vector<int> > &open_list, vector<vector<State> > &grid, int end[2])
{
    int x = c_node[0];
    int y = c_node[1];
    int g = c_node[2];

    // loop through current node's potential neighbors
    for(int i = 0; i < 4; i++)
    {
        int x2 = x + delta[i][0];
        int y2 = y + delta[i][1];

        // check that neighbor is on the grid and not an obstacle
        if(CheckValidCell(x2, y2, grid))
        {
            int g2 = g + 1;
            int h2 = Heuristic(x2, y2, end[0], end[1]);
            AddToOpen(x2, y2, g2, h2, open_list, grid);
        }
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
    while(!open_list.empty())
    {
        CellSort(&open_list);
        vector<int> c_node = open_list.back();
        open_list.pop_back();
        int c_x = c_node[0];
        int c_y = c_node[1];
        grid[c_x][c_y] = State::kPath;

        // check to see if we reached to goal
        if(c_x == end[0] && c_y == end[1])
        {
            grid[start[0]][start[1]] = State::kStart;
            grid[end[0]][end[1]] = State::kFinish;
            return grid;
        }

        // if we're done, then expand search to current node's neighbors
        ExpandNeighbors(c_node, open_list, grid, end);
    }
    cout << "Oh no, there isn't a path to the end" << endl;
    return vector<vector<State> > {};
}

// main function
int main()
{
    int start[2];
    int end[2];
    string path = "./examplemaze.txt";
    vector<vector<State> > board = ReadBoardFile(path);
    cout << "Give starting node (top left is (0, 0)): " << endl;
    cin >> start[0] >> start[1];
    cout << "Give ending node(bottom right is (" << board.size()-1 << ", " << board[0].size()-1 << "):" << endl;
    cin >> end[0] >> end[1];
    cout << "Starting from: (" << start[0] << ", " << start[1] << ")" << endl;
    cout << "Ending at: (" << end[0] << ", " << end[1] <<  ")" << endl;
    auto solution_path = Search(board, start, end);
    PrintTheBoard(solution_path);
}

