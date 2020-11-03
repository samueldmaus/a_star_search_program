#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* moved to .txt file
vector<vector<int> > board = {{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0}};
*/

enum class State {kNothing, kObstacle};

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

int main()
{
    string path = "./examplemaze.txt";
    vector<vector<State> > board = ReadBoardFile(path);
    PrintTheBoard(board);
}

