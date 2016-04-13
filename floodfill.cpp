#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <list>

using namespace std;

class Coord
{
    public:
        int x;
        int y;
        int val;
        Coord(int x, int y, int val)
        {
            this->x = x;
            this->y = y;
            this->val = val;
        }
};
    
int floodfill(int maze[][8], int x,int y)
{
    int currVal = 0;
    Coord * start = new Coord(x,y,0);
    maze[x][y] = currVal;
    list <Coord *> s;
    s.push_back(start);
    while(!(s.empty()))
    {
        Coord * current = s.front();
        s.pop_front();
        if(current->x - 1 >= 0)
        {
            int testX = current->x - 1;
            int testY = current->y;

            if (maze[testX][testY] < 0 && maze[testX][testY] != -1)
            {
                maze[testX][testY] = current->val + 1;
                s.push_back(new Coord(testX, testY, current->val + 1)) ;
            }
        }
        if(current->y - 1 >= 0)
        {
            int testX = current->x;
            int testY = current->y - 1;

            if (maze[testX][testY] < 0 && maze[testX][testY] != -1)
            {
                maze[testX][testY] = current->val + 1;
                s.push_back(new Coord(testX, testY, current->val + 1));
            }
        }
        if(current->x + 1 <= 7)
        {
            int testX = current->x + 1;
            int testY = current->y;

            if (maze[testX][testY] < 0 && maze[testX][testY] != -1)
            {
                maze[testX][testY] = current->val + 1;
                s.push_back(new Coord(testX, testY,current->val + 1));
            }
        }
        if(current->y + 1 <= 7)
        {
            int testX = current->x;
            int testY = current->y + 1;

            if (maze[testX][testY] < 0 && maze[testX][testY] != -1)
            {
                maze[testX][testY] = currVal + 1;
                s.push_back(new Coord(testX, testY, current->val + 1));
            }
        }
    }
    return 0;
}
void buildMaze(int maze[][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(j == 1)
            {
                maze[i][j] = -2;
            }
            else if(i != 0 && j == 3)
            {
                maze[i][j] = -2;
            }
            else if(i == 4 && j == 2)
            {
                maze[i][j] = -2;
            }
            else if(i == 1 && j > 2 && j < 7)
            {
                maze[i][j] = -2;
            }
            else if(i == 7 && j > 2)
            {
                maze[i][j] = -2;
            }
            else if(i > 0 && i < 5 && j == 6)
            {
                maze[i][j] = -2;
            }
            else if(i > 3 && j == 7) 
            {
                maze[i][j] = -2;
            }
            else
            {
                maze[i][j] = -1;
            }
        }
    }
}
void printMaze(int maze[][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(maze[i][j] >= 0 && maze[i][j] < 10)
            {
                cout << "+" << maze[i][j] << " ";
            }
            else
            {
                cout << maze[i][j] << " ";
            }
        }
        cout << endl;
    }
}
int main() {
    int maze[18][18];
    buildMaze(maze);
    printMaze(maze);
    floodfill(maze,4,6);
    cout << endl;
    cout << " ***** The floodFill ***** " << endl;
    cout << endl;
    printMaze(maze);

    return 0;
}

