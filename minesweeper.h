
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

#define MAXROWCOL 100
//================================================================================================
class Minesweeper {

private:
	int ROW;
	int COL;
	int bombs;
	vector<vector<string>> ans_map;
	vector<vector<string>> play_map;

public:
	Minesweeper();
	//Minesweeper(bool exist) {}
	void Save(); //save data to file
	void Load(); //load data from file
	void Print(); //
	bool Check(int, int);
};
//================================================================================================
Minesweeper::Minesweeper()
{
	bombs = 0;
	cout << "Enter for rows: ";
	cin >> ROW;

	cout << "Enter for colums: ";
	cin >> COL;
	
	ans_map.resize(ROW);
	play_map.resize(ROW);

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (rand() % 100 < 17)
			{
				ans_map[i].push_back("B");
				bombs++;
			}
			else
			{
				ans_map[i].push_back("0");
			}
			play_map[i].push_back("-");
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
			if (ans_map[i][j] != "B")
			{
				if (i == 0) //first row of map
				{
					//first full edge
					if (j != COL - 1)
					{
						if (ans_map[i][j + 1] == "B")
						{
							bombcount++;
						}
						if (ans_map[i + 1][j + 1] == "B")
						{
							bombcount++;
						}
					}
					//second full edge
					if (j != 0)
					{
						if (ans_map[i][j - 1] == "B")
						{
							bombcount++;
						}
						if (ans_map[i + 1][j - 1] == "B")
						{
							bombcount++;
						}
					}
					if (ans_map[i + 1][j] == "B")
					{
						bombcount++;
					}

				}
				else if (i == ROW - 1)
				{
					//third full edge
					if (j != COL - 1)
					{
						if (ans_map[i][j + 1] == "B")
						{
							bombcount++;
						}
						if (ans_map[i - 1][j + 1] == "B")
						{
							bombcount++;
						}
					}
					//fourth full edge
					if (j != 0)
					{
						if (ans_map[i][j - 1] == "B")
						{
							bombcount++;
						}
						if (ans_map[i - 1][j - 1] == "B")
						{
							bombcount++;
						}
					}
					if (ans_map[i - 1][j] == "B")
					{
						bombcount++;
					}
				}
				else
				{
					//edges at first column
					if (j != COL - 1)
					{
						if (ans_map[i - 1][j + 1] == "B")
						{
							bombcount++;
						}
						if (ans_map[i][j + 1] == "B")
						{
							bombcount++;
						}
						if (ans_map[i + 1][j + 1] == "B")
						{
							bombcount++;
						}
					}
					//edges at last column
					if (j != 0)
					{
						if (ans_map[i - 1][j - 1] == "B")
						{
							bombcount++;
						}
						if (ans_map[i][j - 1] == "B")
						{
							bombcount++;
						}
						if (ans_map[i + 1][j - 1] == "B")
						{
							bombcount++;
						}
					}
					if (ans_map[i - 1][j] == "B")
					{
						bombcount++;
					}
					if (ans_map[i + 1][j] == "B")
					{
						bombcount++;
					}
				}
				ans_map[i][j] = to_string(bombcount);
			}
		}
	}

}
//================================================================================================
void Minesweeper::Save()
{
	fstream load;
	// From line 13 to 30 is to create a new file if the file is not exist
	load.open(".txt");

	try
	{
		if (!load.is_open())
		{
			load.close();
			load.open(".txt", fstream::out);
			load.close();
			throw ("File does not exist, generating loader data file loader.txt");
		}
	}
	catch (const runtime_error& error)
	{
		cerr << error.what() << endl;
	}
	load.close();


	load.open("loader.txt", fstream::out);
	// This is where you save the data into file
	//
	//
	//
	load.close();

	return;
}
//================================================================================================
void Minesweeper::Load()
{
	ifstream load;
	load.open("loader.txt", fstream::in);
	try
	{
		if (!load.is_open())
		{
			load.close();
			throw ("loader.txt File does not Exist");
		}
		if (load.peek() == EOF)
		{
			load.close();
			throw ("loader.txt File is empty, no data saved");
		}

		// This is where you read the data
		//
		//
		//

		load.close();

	}
	catch (const runtime_error& error)
	{
		cerr << error.what() << endl;
	}

	return;
}
//================================================================================================
void Minesweeper::Print()
{
	//print first row numbers
	cout << "   ";
	for (int i = 1; i <= ROW; i++)
	{
		if (i < 10)
		{
			cout << "0" << i << " ";
		}
		else
		{
			cout << i << " ";
		}
		
	}
	cout << endl;
	for (int x = 0; x < play_map.size(); x++) {
		
		for (int y = 0; y < play_map[x].size(); y++) {
			if (y == 0)
			{
				if (x < 9)
				{
					cout << "0" << x + 1 << " ";
				}
				else
				{
					cout << x + 1 << " ";
				}
			}
			cout << play_map[x][y] << "  ";
		}
		cout << endl;
	}
}
//================================================================================================
bool Minesweeper::Check(int i, int j)
{
	if (ans_map[i][j] != "B")
	{
		play_map[i][j] = ans_map[i][j];
	}
	else
	{
		for (unsigned int x = 0; x < play_map.size(); x++) {
			for (unsigned int y = 0; y < play_map[x].size(); y++) {
				if (ans_map[x][y] == "B")
				{
					play_map[x][y] = ans_map[x][y];
				}
			}
		}
		return true;
	}
	return false;
}
//================================================================================================
void CoolStuff(int x, int y)
{
	while (true)
	{

	}
}
