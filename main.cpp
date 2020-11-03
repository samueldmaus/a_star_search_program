#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int> > board = {{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0},
{0, 0, 0, 0, 1, 0}};

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
    PrintTheBoard(board);
}

