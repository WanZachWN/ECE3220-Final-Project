#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
#define MINROWCOL 3
#define MAXROWCOL 100
#define MAXDIFF 99
#define MINDIFF 1
//================================================================================================
class Minesweeper {

private:
	int ROW, COL, DIFF;
	vector<vector<string>> ans_map;
	vector<vector<string>> play_map;

public:
	Minesweeper(); //Default Constructor
	~Minesweeper(){}
	void Save();
	void Load();
	bool Check(int, int);
	friend void Print(Minesweeper); 

};
//================================================================================================
Minesweeper::Minesweeper()
{
	while (1)
	{
		cout << "Enter for map rows: ";
		cin >> ROW;
		if (ROW >= MINROWCOL && ROW <= MAXROWCOL)
		{
			break;
		}
	}

	while (1)
	{
		cout << "Enter for map colums: ";
		cin >> COL;
		if (COL >= MINROWCOL && COL <= MAXROWCOL)
		{
			break;
		}
	}

	while (1)
	{
		cout << "Enter difficulty (1 - 99): ";
		cin >> DIFF;
		if (DIFF >= MINDIFF && DIFF <= MAXDIFF)
		{
			break;
		}
	}


	ans_map.resize(ROW);
	play_map.resize(ROW);
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (rand() % (ROW*COL) < DIFF)
			{
				ans_map[i].push_back("B");
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
	fstream save;
	// From line 13 to 30 is to create a new file if the file is not exist
	save.open("gfmindreader.txt");

	try
	{
		if (!save.is_open())
		{
			save.close();
			save.open("gfmindreader.txt", fstream::out);
			save.close();
			throw ("File does not exist, generating loader data file loader.txt");
		}
	}
	catch (const runtime_error& error)
	{
		cerr << error.what() << endl;
	}
	save.close();


	save.open("gfmindreader.txt", fstream::out);

	save << ROW << " " << COL << endl;

	// This is where you save the data into file
	for(int x = 0; x < play_map.size(); x++) {
		for (int y = 0; y < play_map[x].size(); y++) {
			save << play_map[x][y];
		}
		save << endl;
	}
	save << endl;
	//save ans map
	for (int x = play_map.size()-1; x > -1; x--) {
		for (int y = play_map[x].size()-1; y > -1 ; y--) {
			save << ans_map[x][y];
		}
		save << endl;
	}
	save << endl;

	save.close();

	return;
}
//================================================================================================
void Minesweeper::Load()
{
	ifstream load;
	load.open("gfmindreader.txt", fstream::in);
	try
	{
		if (!load.is_open())
		{
			load.close();
			throw ("gfmindreader.txt File does not Exist");
		}
		if (load.peek() == EOF)
		{
			load.close();
			throw ("gfmindreader.txt File is empty, no data saved");
		}

		// This is where you read the data
		int i = 0;
		string content;
		while (true)
		{
			if (i == 0)
			{
				load >> content;
				ROW = atoi(&content[0]);
				COL = atoi(&content[2]);
				i++;
				content.clear();
			}
			else
			{

			}



		}

		load.close();

	}
	catch (const runtime_error& error)
	{
		cerr << error.what() << endl;
	}

	return;
}
//================================================================================================
void Print(Minesweeper mine)
{
	//print first row numbers
	cout << "   ";
	for (int i = 1; i <= mine.ROW; i++)
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
	for (int x = 0; x < mine.play_map.size(); x++) {
		
		for (int y = 0; y < mine.play_map[x].size(); y++) {
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
			cout << mine.play_map[x][y] << "  ";
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
		/*if (ans_map[i][j] == "0")
		{
			CoolStuff(i, j);
		}*/

	}
	else
	{
		for (int x = 0; x < play_map.size(); x++) {
			for (int y = 0; y < play_map[x].size(); y++) {
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
//================================================================================================
