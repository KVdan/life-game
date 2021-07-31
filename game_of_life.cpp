// File: life.cpp
// Author: d coles

// Implements the Game of Life. Each square is in a 20x20 array is
// in one of two possible states: alive or dead. The next configuration
// is computed by counting simultaneously the number of living
// neighbors for each cell. If a cell has 2 living neighbors, then
// its status does not change; if 3 living neighbors, then it will be
// alive in the next generation; any other number of living neighbors
// and it will be dead in the next generation.

#include <iostream>

using namespace std;
const int Size = 20;
void displayGrid(const bool[][Size]);
void nextGeneration(bool[][Size], bool[][Size]);
int getNeighborCount(const bool[][Size], int, int);

int main()
{
    cout << "Here is the Game of Life on a 20x20 grid.\n\n";

    cout << "You will be prompted to enter integer pairs corresponding\n"
         << "to rows and columns of cells that you wish to be initially\n"
         << "living. The cells are numbered from (0,0) to (19,19)\n"
         << "Enter -1 -1 to quit.\n\n";

    // Initialize the grid to all dead cells
    bool Grid[Size][Size];
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            Grid[i][j] = false;

    int row, col;

    // Prompt user for initially living cells. Ignore illegal inputs.
    do
    {
        cout << "\nEnter a row and column, separated by a space: ";
        cin >> row >> col;
        if (row >= 0 && row < Size && col >= 0 && col < Size) // if legal row-col
            Grid[row][col] = true;
    } while (row != -1);

    displayGrid(Grid);

    char userResponse;
    bool temp[Size][Size]; // temporary workspace for computing next generation
    cout << "\nDo you want to see the next generation (y/n)? ";
    cin >> userResponse;
    while (userResponse == 'y' || userResponse == 'Y')
    {
        nextGeneration(Grid, temp);
        displayGrid(Grid);
        cout << "\nDo you want to see the next generation (y/n)? ";
        cin >> userResponse;
    }

    return 0;
}

void displayGrid(const bool World[][Size])
{
    cout << '\n';
    for (int i = 0; i < Size; i++)
    {
        for (int j = 0; j < Size; j++)
            if (World[i][j] == true)
                cout << "X ";
            else
                cout << ". ";

        cout << '\n';
    }
}

// Declares a local array of states and sets it to the next generation
// by looping thru the object's World array, and for each cell calling
// the getNeighborCount function to see whether it should live or die.
// Once the temporary array is filled, it is copied over to the
// object's World array.
void nextGeneration(bool World[][Size], bool tempWorld[][Size])
{
    int neighborCnt;
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
        {
            neighborCnt = getNeighborCount(World, i, j);
            if (neighborCnt == 2)              // 2 live neighbors:
                tempWorld[i][j] = World[i][j]; // unchanged in next generation.
            else if (neighborCnt == 3)
                tempWorld[i][j] = true; // 3 live neighbors:
                                        // alive in next generation
            else
                tempWorld[i][j] = false; // 1, 4-8 living neighbors:
        }                                // dead in next generation

    // copy tempWorld to World
    for (int i = 0; i < Size; i++)
        for (int j = 0; j < Size; j++)
            World[i][j] = tempWorld[i][j];
}

int getNeighborCount(const bool World[][Size], const int row, const int col)
// This function takes a row/col pair and counts the number
// of living neighbors for the specified cell.
{
    //  1 2 3       These are the positions of the
    //  4 x 5       neighbors of x. Each is checked
    //  6 7 8       below for alive/dead.

    int cnt = 0;
// 我修改了此部分
    if (World[row - 1][col - 1] == true) // check 1
        cnt++;
    if (World[row - 1][col + 1] == true) // check 3
        cnt++;
    if (World[row - 1][col] == true) // check 2
        cnt++;
    if (World[row + 1][col - 1] == true) // check 6
        cnt++;
    if (World[row + 1][col + 1] == true) // check 8
        cnt++;
    if (World[row + 1][col] == true) // check 7
        cnt++;
    if (World[row][col - 1] == true) // check 4
        cnt++;
    if (World[row][col + 1] == true) // check 5
        cnt++;

    return cnt;
}
