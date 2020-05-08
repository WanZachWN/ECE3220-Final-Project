#include <iostream>
#include <cstdlib>
#include <vector>
 
using namespace std;

#define MAXROWCOL 100
//================================================================================================
class Minesweeper {

private:
	int ROW;
	int COL;
	int bombs;
	vector<vector<char>> map;

public:
	Minesweeper() {}
	Minesweeper(bool exist) {}
	void Save();
	void Load();
	void Print();
	void Check();
	void Choice();
};
//================================================================================================
Minesweeper::Minesweeper()
{
	cout << "Enter for rows: ";
	cin >> ROW;

	cout << "Enter for colums: ";
	cin >> COL;

	map.resize(ROW);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (rand() % 100 < 17)
			{
				map[i].push_back('B');
			}
			else
			{
				map[i].push_back('0');
			}
		}
	}
	/* type of cases
	- four different full edges
	- first row edges
	- last row edges
	- first column edges
	- last column edges
	- middle
	*/
	int bombcount;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			bombcount = 0;
			if (map[i][j] != 'B')
			{
				if (i == 0) //first row of map
				{
					//first full edge
					if(j != COL - 1)
					{
						if (map[i][j + 1] == 'B')
						{
							bombcount++;
						}
						if (map[i + 1][j + 1] == 'B')
						{
							bombcount++;
						}
					}
					//second full edge
					if (j != 0)
					{
						if (map[i][j - 1] == 'B')
						{
							bombcount++;
						}
						if (map[i + 1][j - 1] == 'B')
						{
							bombcount++;
						}
					}
					if (map[i + 1][j] == 'B')
					{
						bombcount++;
					}

				}
				else if (i == ROW - 1)
				{
					//third full edge
					if (j != COL - 1)
					{
						if (map[i][j + 1] == 'B')
						{
							bombcount++;
						}
						if (map[i - 1][j + 1] == 'B')
						{
							bombcount++;
						}
					}
					//fourth full edge
					if (j != 0)
					{
						if (map[i][j - 1] == 'B')
						{
							bombcount++;
						}
						if (map[i - 1][j - 1] == 'B')
						{
							bombcount++;
						}
					}
					if (map[i - 1][j] == 'B')
					{
						bombcount++;
					}
				}
				else
				{
					//edges at first column
					if (j != COL - 1)
					{
						if (map[i - 1][j + 1] == 'B')
						{
							bombcount++;
						}
						if (map[i][j + 1] == 'B')
						{
							bombcount++;
						}
						if (map[i + 1][j + 1] == 'B')
						{
							bombcount++;
						}
					}
					//edges at last column
					if (j != 0)
					{
						if (map[i - 1][j - 1] == 'B')
						{
							bombcount++;
						}
						if (map[i][j - 1] == 'B')
						{
							bombcount++;
						}
						if (map[i + 1][j - 1] == 'B')
						{
							bombcount++;
						}
					}
					if (map[i - 1][j] == 'B')
					{
						bombcount++;
					}
					if (map[i + 1][j] == 'B')
					{
						bombcount++;
					}
				}
				map[i][j] = bombcount;
			}
		}
	}

}
//================================================================================================
void Minesweeper::Save()
{

}
//================================================================================================
void Minesweeper::Load()
{

}
//================================================================================================
void Minesweeper::Print()
{

}
//================================================================================================
void Minesweeper::Check()
{

}
//================================================================================================
void Minesweeper::Choice()
{

}
//================================================================================================
