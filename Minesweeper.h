#include <iostream> //input and output streams
#include <cstdlib> //string manipulator
#include <vector> //vector class
#include <fstream> //file stream class
#include <string> //string class
#include <iomanip>//used for setw() and setfill()

using namespace std; //namespace for std

#define MINROWCOL 3 //minimum row and column allowed to be generated
#define MAXROWCOL 100 //maximum row and column allowed to be generated
#define MAXDIFF 99 // maximum difficulty allowed to be generated
#define MINDIFF 1 //minimum difficulty allowed to be generated
//================================================================================================
/* Class Map
   - generate map class that has public members
   - Row and Column type integer to store map size
   - vector string that stores all the answers of the bombs and number values 
     of how many bombs surrounding the non-bomb tile
   - vector string that stores the play map that the user sees
   - Map constructors that initialize Row and Column of the map to 0
*/
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
/* Class FileIO
   - generate FileIO class that has public operations
   - Save function that is a void type and accepts a Map reference type
   - Load function that returns a bool and accepts a Map reference type
   - Delete function that is a void type
*/
class FileIO {
	public:
		void Save(Map&);
		bool Load(Map&);
		void Delete();
};
//================================================================================================
/* Class Minesweeper
   - generate Minesweeper class that has private and public operations
   - private member DIFF type int to store difficulty when user create new game
   - private member lose type bool to check if user lose or win
   - public member map type Map class pointer
   - public member io type FileIO class pointer
   - Minesweeper default constructor that initialize DIFF to 0 and lose to false
   - Minesweeper destructor
     - deletes the content that map pointer is pointing to and set the map pointer to NULL
     - deletes the content that io pointer is pointing to ans set the io pointer to NULL
   - Void type function GenerateMap that generates map for a new game
   - Void type Check that accepts two parameters type integer to check if user input is valid
   - friend bool type function GetWin that accepts a Minesweeper class reference
     to check if the user win the game
   - friend bool type function GetLose that accepts a Minesweeper class reference
     to check if the user lose the game
   - friend void type function Print that accepts a Map class reference
     to print the current map
*/
class Minesweeper {

	private:
		int DIFF;
		bool lose;
		
	public:
		Map* map = new Map();
		FileIO *io = new FileIO();
		Minesweeper()//Default Constructor
		{
			DIFF = 0;
			lose = false;
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
/*
  GenerateMap function belong to Minesweeper class that generates new map 
  for user that chooses new game
*/
void Minesweeper::GenerateMap()
{
	//ask the user to enter rows for the map
	while (1)
	{
		cout << "Enter for map rows: ";
		cin >> this->map->ROW;
		
		//if user enters in between the min and max grid set then break the loop
		if (this->map->ROW >= MINROWCOL && this->map->ROW <= MAXROWCOL)
		{
			break;
		}
	}
	//ask the user to enter columns for the map
	while (1)
	{
		cout << "Enter for map colums: ";
		cin >> this->map->COL;
		
		//if user enters in between the min and max grid set then break the loop
		if (this->map->COL >= MINROWCOL && this->map->COL <= MAXROWCOL)
		{
			break;
		}
	}
	//ask the user to enter difficulty for the map
	while (1)
	{
		cout << "Enter difficulty (1 - 99): ";
		cin >> DIFF;
	
		//if user enters in between the min and max grid set then break the loop
		if (DIFF >= MINDIFF && DIFF <= MAXDIFF)
		{
			//difficulty is set to percentage of the grid
			DIFF = (this->map->ROW * this->map->COL) * DIFF;
			DIFF = DIFF / 100;
			break;
		}
	}

	//resize the vectors
	this->map->ans_map.resize(this->map->ROW);
	this->map->play_map.resize(this->map->ROW);
	
	//loop to generate bombs
	for (int i = 0; i < this->map->ROW; i++)
	{
		for (int j = 0; j < this->map->COL; j++)
		{
			if (rand() % 100 < DIFF)
			{
				this->map->ans_map[i].push_back("B");
			}
			else
			{	//push back 0 as temporary while generating bombs
				this->map->ans_map[i].push_back("0");
			}
			this->map->play_map[i].push_back("-");//set play map to "-" as closed tiles
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
	int bombcount; // counter for bombs surrounding each tile
	//loop the whole answer map and set the 0 to the number of bombs surrounding it
	for (int i = 0; i < this->map->ROW; i++)
	{
		for (int j = 0; j < this->map->COL; j++)
		{
			bombcount = 0;//initialize to 0 everytime we check new tile
			//if does not equal to the bomb
			if (this->map->ans_map[i][j] != "B")
			{
				if (i == 0) //first row of map
				{
					//top edges will go through the whole if statement
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
					//all first row tiles will check beneath it
					if (this->map->ans_map[i + 1][j] == "B")
					{
						bombcount++;
					}

				}
				//last row of the map
				else if (i == this->map->ROW - 1)
				{
					//bottom edges will go through the whole if statement
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
					//all last row tile will check above it
					if (this->map->ans_map[i - 1][j] == "B")
					{
						bombcount++;
					}
				}
				//middle tiles, left edges and right edges
				else
				{
					//middle tiles will go through the whole if statements
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
					//all middle, left edges and right edges tile will check
					//above and beneath them
					if (this->map->ans_map[i - 1][j] == "B")
					{
						bombcount++;
					}
					if (this->map->ans_map[i + 1][j] == "B")
					{
						bombcount++;
					}
				}
				//set the 0 tile to how many bombs surrounding it
				this->map->ans_map[i][j] = to_string(bombcount);
			}
		}
	}

}
//================================================================================================
/*
  Save function belong to FileIO class that saves the map to a txt file when
  the user wants to save and end the game
*/
void FileIO::Save(Map &map)
{
	fstream save;
	// From line 310 to 327 is to create a new file if the file is not exist
	save.open("gfmindreader.txt");

	try
	{
		//if file fail to open or does not exist
		if (!save.is_open())
		{
			save.close();
			save.open("gfmindreader.txt", fstream::out);//create a new file
			save.close();//close file
			//throw a runtime error
			throw runtime_error("File does not exist, generating save game data file gfmindreader.txt");
		}
	}
	catch (const runtime_error& error)//catch block
	{
		cerr << error.what() << endl;
	}
	//close the file again if the file exist and opened before
	if(save.is_open())
	{
		save.close();
	}

	//open it again to rewrite data. previous saved files will be deleted
	save.open("gfmindreader.txt", fstream::out);
	
	//store the row of the map
	save << map.ROW;
	save << "\n";
	//store the column of the map
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
 	//close the file after wrinting to it
	save.close();

	return;
}
//================================================================================================
/*
  Load function belong to FileIO class that loads the map saved in txt file 
  when user chooses to load the game from a save point
*/
bool FileIO::Load(Map& map)
{
	ifstream load;
	load.open("gfmindreader.txt", fstream::in);
	
	try
	{	
		//if file does not exist throw exception
		if (!load.is_open())
		{
			load.close();
			throw runtime_error("gfmindreader.txt File does not Exist");
		}
		//if file is empty throw exception
		if (load.peek() == EOF)
		{
			load.close();
			throw runtime_error("gfmindreader.txt File is empty, no data saved");
		}

		
		// This is where you read the data and generate saved map
		string content;
		//read the row and store it to the map
		load >> content;
		map.ROW = stoi(content);
		//read the column and store it to the map
		load >> content;
		map.COL = stoi(content);
		
		//resize the map before reading the map contents in the saved file
		map.ans_map.resize(map.ROW);
		map.play_map.resize(map.ROW);

		//loading play map
		for (int i = 0; i < map.ROW; i++) {
			for (int j = 0; j < map.COL; j++) {

				load >> content;
				map.play_map[i].push_back(content);
			}
		}
		//load answer map
		for (int i = 0; i < map.ROW; i++) {
			for (int j = 0; j < map.COL; j++) {
				load >> content;
				map.ans_map[i].push_back(content);
			}
		}

		load.close();//close the file

	}
	//catch block if there is no save file found
	catch (const runtime_error& error)
	{
		cerr << error.what() << endl;
		return false;
	}

	return true;
}
//================================================================================================
/*
  Print function friend to Minesweeper class that prints the play map 
*/
void Print(Map &map)
{
	//print first row number reference
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
	//print the map and first column number reference
	for (int x = 0; x < map.play_map.size(); x++) {
		
		for (int y = 0; y < map.play_map[x].size(); y++) {
			//if first column element then print the first column number reference
			if (y == 0)
			{
				cout << setw(2) << setfill('0') << x + 1 << " ";
			}
			//print the current tile of the play map
			cout << map.play_map[x][y] << "  ";
		}
		cout << endl;
	}
}
//================================================================================================
/*
  Check function belong to Minesweeper class that checks the user input is valid(using recursion method)
*/
void Minesweeper::Check(int i, int j)
{
	//if user input row is less than 1 or more than set grid row
	if (i < 0 || i >= this->map->ROW)
	{
		return;
	}
	//if user input column is less than 1 or more than set grid row
	if (j < 0 || j >= this->map->COL)
	{
		return;
	}
	//if the tile is already opened up
	if (this->map->play_map[i][j] != "-")
	{
		return;
	}
	//if the tile is not a bomb
	if (this->map->ans_map[i][j] != "B")
	{
		//open the current tile
		this->map->play_map[i][j] = this->map->ans_map[i][j];
		//if it is zero then reveal other tiles surrounding it untill
		//it reaches a numbered tile and open that tile and return
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
	//if it is a bomb tile then replace all the closed bomb tile with the bomb
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
		this->lose = true;//set the lose variable to true to indicate that the player has lost
	}
	return;
}
//================================================================================================
/*
  GetWin function friend to Minesweeper class that checks if the user wins the game
*/
bool GetWin(Minesweeper &mine)
{
	//checks the whole play map to see if the user wins
	for (int i = 0; i < mine.map->ROW; i++)
	{
		for (int j = 0; j < mine.map->COL; j++)
		{
			//if the map is a unopened tile and it is not a bomb then
			//the user has not won the game
			if (mine.map->play_map[i][j] == "-")
			{
				if (mine.map->ans_map[i][j] != "B")
				{
					return false;
				}
			}
		}
	}
	//if we reach here then the user has won the game
	return true;
}
//================================================================================================
/*
  GetLose function friend to Minesweeper class that checks if the user lose the game
*/
bool GetLose(Minesweeper& mine)
{
	return mine.lose; //returns the lose variable from minesweeper class
}
//================================================================================================
/*
  Delete function belong to FileIO class that clears the save file when the user wins
*/
void FileIO::Delete()
{
	//clear the content of the text file
	fstream clear;
	clear.open("gfmindreader.txt", fstream::out);
	clear.close();

	return;
}
