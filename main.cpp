#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/* moved to .txt file
vector<vector<int> > board = {{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0}};
*/

void ReadBoardFile(string file)
{
    string line;
    ifstream the_board(file);
    while(getline(the_board, line))
    {
        cout << line << endl;
    }
}

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
    ReadBoardFile(path);
}

