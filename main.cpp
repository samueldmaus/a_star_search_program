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

// parse through each line of the .txt file
vector<int> ParseLine(string &line)
{
    istringstream i_line(line);
    int n; char c; vector<int> p_vector;
    while(i_line >> n >> c && c == ',')
    {
        p_vector.push_back(n);
    }
    return p_vector;

}

// print the contents from the .txt file
vector<vector<int> >ReadBoardFile(string &file)
{
    // string variable for the each lin & vector<vector<int>> var for the board
    string line;
    vector<vector<int> > parsed_vector;

    // ifstream to take in the .txt file
    ifstream the_board(file);

    // if to make sure fstream worked; push_back each line into the parsed vector
    if(the_board)
    {
        while(getline(the_board, line))
        {
            parsed_vector.push_back(ParseLine(line));
        }
    }

    return parsed_vector;
}

// print the board to the console
void PrintTheBoard(vector<vector<int> > &v)
{
    for(vector<int> i : v)
    {
        for(int j : i)
        {
            cout << j;
        }
        cout << endl;
    }
}

int main()
{
    string path = "./examplemaze.txt";
    vector<vector<int> > board = ReadBoardFile(path);
    PrintTheBoard(board);
}

