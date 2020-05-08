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
class Map {
	public:
		int ROW, COL;
		vector<vector<string>> ans_map;
		vector<vector<string>> play_map;
		Map()
		{
			ROW = 0;
			COL = 0;
		}
};
//================================================================================================
class FileIO {
	public:
		void Save(Map&);
		bool Load(Map&);
		void Delete();
};
//================================================================================================
class Minesweeper {

	private:
		int DIFF;
		bool lose, load;
		
	public:
		Map* map = new Map();
		FileIO *io = new FileIO();
		Minesweeper()//Default Constructor
		{
			DIFF = 0;
			lose = false;
			load = false;
		}
		~Minesweeper()
		{
			delete map;
			map = NULL;
			delete io;
			io = NULL;
		}
		void GenerateMap();
		void Check(int, int);
		friend bool GetWin(Minesweeper&);
		friend bool GetLose(Minesweeper&);
		friend void Print(Map&);

};
//================================================================================================
void Minesweeper::GenerateMap()
{
	while (1)
	{
		cout << "Enter for map rows: ";
		cin >> this->map->ROW;
		if (this->map->ROW >= MINROWCOL && this->map->ROW <= MAXROWCOL)
		{
			break;
		}
	}

	while (1)
	{
		cout << "Enter for map colums: ";
		cin >> this->map->COL;
		if (this->map->COL >= MINROWCOL && this->map->COL <= MAXROWCOL)
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
			DIFF = (this->map->ROW * this->map->COL) * DIFF;
			DIFF = DIFF / 100;
			break;
		}
	}


	this->map->ans_map.resize(this->map->ROW);
	this->map->play_map.resize(this->map->ROW);
	for (int i = 0; i < this->map->ROW; i++)
	{
		for (int j = 0; j < this->map->COL; j++)
		{
			if (rand() % (this->map->ROW * this->map->COL) < DIFF)
			{
				this->map->ans_map[i].push_back("B");
			}
			else
			{
				this->map->ans_map[i].push_back("0");
			}
			this->map->play_map[i].push_back("-");
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
	for (int i = 0; i < this->map->ROW; i++)
	{
		for (int j = 0; j < this->map->COL; j++)
		{
			bombcount = 0;
			if (this->map->ans_map[i][j] != "B")
			{
				if (i == 0) //first row of map
				{
					//first full edge
					if (j != this->map->COL - 1)
					{
						if (this->map->ans_map[i][j + 1] == "B")
						{
							bombcount++;
						}
						if (this->map->ans_map[i + 1][j + 1] == "B")
						{
							bombcount++;
						}
					}
					//second full edge
					if (j != 0)
					{
						if (this->map->ans_map[i][j - 1] == "B")
						{
							bombcount++;
						}
						if (this->map->ans_map[i + 1][j - 1] == "B")
						{
							bombcount++;
						}
					}
					if (this->map->ans_map[i + 1][j] == "B")
					{
						bombcount++;
					}

				}
				else if (i == this->map->ROW - 1)
				{
					//third full edge
					if (j != this->map->COL - 1)
					{
						if (this->map->ans_map[i][j + 1] == "B")
						{
							bombcount++;
						}
						if (this->map->ans_map[i - 1][j + 1] == "B")
						{
							bombcount++;
						}
					}
					//fourth full edge
					if (j != 0)
					{
						if (this->map->ans_map[i][j - 1] == "B")
						{
							bombcount++;
						}
						if (this->map->ans_map[i - 1][j - 1] == "B")
						{
							bombcount++;
						}
					}
					if (this->map->ans_map[i - 1][j] == "B")
					{
						bombcount++;
					}
				}
				else
				{
					//edges at first column
					if (j != this->map->COL - 1)
					{
						if (this->map->ans_map[i - 1][j + 1] == "B")
						{
							bombcount++;
						}
						if (this->map->ans_map[i][j + 1] == "B")
						{
							bombcount++;
						}
						if (this->map->ans_map[i + 1][j + 1] == "B")
						{
							bombcount++;
						}
					}
					//edges at last column
					if (j != 0)
					{
						if (this->map->ans_map[i - 1][j - 1] == "B")
						{
							bombcount++;
						}
						if (this->map->ans_map[i][j - 1] == "B")
						{
							bombcount++;
						}
						if (this->map->ans_map[i + 1][j - 1] == "B")
						{
							bombcount++;
						}
					}
					if (this->map->ans_map[i - 1][j] == "B")
					{
						bombcount++;
					}
					if (this->map->ans_map[i + 1][j] == "B")
					{
						bombcount++;
					}
				}
				this->map->ans_map[i][j] = to_string(bombcount);
			}
		}
	}

}
//================================================================================================
void FileIO::Save(Map &map)
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
			throw runtime_error("File does not exist, generating loader data file gfmindreader.txt");
		}
	}
	catch (const runtime_error& error)
	{
		cerr << error.what() << endl;
	}
	save.close();


	save.open("gfmindreader.txt", fstream::out);

	save << map.ROW;
	save << "\n";
	save << map.COL;
	save << "\n";
	//Save the play_map
	for (int i = 0; i < map.play_map.size(); i++) {
		for (int j = 0; j < map.play_map[i].size(); j++) {
			save << map.play_map[i][j];
			save << "\n";
		}
	}
	//Save the ans_map
	for (int x = 0; x < map.ans_map.size(); x++) {
		for (int y = 0; y < map.ans_map[x].size(); y++) {
			save << map.ans_map[x][y];
			save << "\n";
		}
	}

	save.close();

	return;
}
//================================================================================================
bool FileIO::Load(Map& map)
{
	ifstream load;
	load.open("gfmindreader.txt", fstream::in);
	try
	{
		if (!load.is_open())
		{
			load.close();
			throw runtime_error("gfmindreader.txt File does not Exist");
		}
		if (load.peek() == EOF)
		{
			load.close();
			throw runtime_error("gfmindreader.txt File is empty, no data saved");
		}


		// This is where you read the data
		string content;

		load >> content;
		map.ROW = stoi(content);
		load >> content;
		map.COL = stoi(content);

		map.ans_map.resize(map.ROW);
		map.play_map.resize(map.ROW);

		//loading play map
		for (int i = 0; i < map.ROW; i++) {
			for (int j = 0; j < map.COL; j++) {

				load >> content;
				map.play_map[i].push_back(content);
			}
		}
		for (int i = 0; i < map.ROW; i++) {
			for (int j = 0; j < map.COL; j++) {
				load >> content;
				map.ans_map[i].push_back(content);
			}
		}

		load.close();

	}
	catch (const runtime_error& error)
	{
		cerr << error.what() << endl;
		return false;
	}

	return true;
}
//================================================================================================
void Print(Map &map)
{
	//print first row numbers
	cout << "   ";
	for (int i = 1; i <= map.ROW; i++)
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
	for (int x = 0; x < map.play_map.size(); x++) {
		
		for (int y = 0; y < map.play_map[x].size(); y++) {
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
			cout << map.play_map[x][y] << "  ";
		}
		cout << endl;
	}
}
//================================================================================================
void Minesweeper::Check(int i, int j)
{
	if (i < 0 || i >= this->map->ROW)
	{
		return;
	}
	if (j < 0 || j >= this->map->COL)
	{
		return;
	}
	if (this->map->play_map[i][j] != "-")
	{
		return;
	}
	if (this->map->ans_map[i][j] != "B")
	{
		this->map->play_map[i][j] = this->map->ans_map[i][j];
		if (this->map->ans_map[i][j] == "0")
		{
			Check(i, j-1);
			Check(i, j+1);
			Check(i-1, j);
			Check(i+1, j);
			Check(i-1, j-1);
			Check(i+1, j+1);
			Check(i-1, j+1);
			Check(i+1, j-1);
		}
	}
	else
	{
		for (int x = 0; x < this->map->play_map.size(); x++) {
			for (int y = 0; y < this->map->play_map[x].size(); y++) {
				if (this->map->ans_map[x][y] == "B")
				{
					this->map->play_map[x][y] = this->map->ans_map[x][y];
				}
			}
		}
		this->lose = true;
	}
	return;
}
//================================================================================================
bool GetWin(Minesweeper &mine)
{
	for (int i = 0; i < mine.map->ROW; i++)
	{
		for (int j = 0; j < mine.map->COL; j++)
		{
			if (mine.map->play_map[i][j] == "-")
			{
				if (mine.map->ans_map[i][j] != "B")
				{
					return false;
				}
			}
		}
	}
	return true;
}
//================================================================================================
bool GetLose(Minesweeper& mine)
{
	return mine.lose;
}
//================================================================================================
void FileIO::Delete()
{
	fstream clear;
	clear.open("gfmindreader.txt", fstream::out);
	clear.close();

	return;
}
