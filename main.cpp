#include "Minesweeper.h"//include header file
//main function
int main()
{
	//set to null so that it can be randomized
	srand(time(NULL));
	//mine type Minesweeper pointer dynamically located
	Minesweeper *mine = new Minesweeper();
	int x = 0; //x coordinate entered by player
	int y = 0; //y coordinate entered by player
	char cont; //char for new game or load and yes or no for save the game
	int exitcode = 0;
	
	//game continues until player ask to stop
	while (true)
	{
		//ask the player if they would like to start a new game or load a saved game
		cout << "Would you like to start a new game or load?" << endl
			<< "n = new game" << endl
			<< "l = load game" << endl;
		cin >> cont;

		if (cont == 'n') //new game requested
		{
			mine->GenerateMap();
			break;
		}
		else if (cont == 'l')//load game requested
		{
			cout << "Loading from a saved game..." << endl;
			
			//load does not exist then start a new game automatically
			if (!mine->io->Load(*mine->map)) 
			{
				cout << "Starting new game..." << endl;
				mine->GenerateMap();
			}
			break;
		}
		//player enters other than 'n' or 'l'
		else
		{
			cout << "Invalid character entry!" << endl;
		}
	}
	
	try {
		//print the initial map
		Print(*mine->map);
		while (true)
		{	
			//ask the player to enter row and column coordinates from the map
			while (true)
			{
				cout << "Enter Row: ";
				cin >> x;
				cout << "Enter Column: ";
				cin >> y;
				//if one of them is invalid then ask the player to re enter
				if (x > 0 && x <= mine->map->ROW) 
				{
					if (y > 0 && y <= mine->map->COL)
					{
						break;
					}
				}
				cout << "Invalid coordinates, exceeds boundaries!" << endl;
			}
			
			//check the entered coordinates whether it is a bomb or not
			mine->Check(x - 1, y - 1);
			
			//print map
			Print(*mine->map);
			
			//if the player has entered a bomb location then tell the player the lost
			if (GetLose(*mine))
			{
				cout << "You Lose!" << endl;
				break;
			}
			//if the player has unlocked all the non-bomb tiles
			//tell the user they won and delete any saved game
			else if (GetWin(*mine))
			{
				cout << "You Win!" << endl;
				mine->io->Delete();
				break;
			}
			//ask if the player wishes to continue if they haven't won or lost
			cout << "Would you like to continue? (y/n): ";
			cin >> cont;
			//if the player does not want to continue then save the map
			if (cont == 'n')
			{
				mine->io->Save(*mine->map);
				break;
			}
		}
		//delete pointer and set it to NULL at end of program
		delete mine;
		mine = NULL;
	}
	catch (...)//catch block for unexpected errors during runtime
	{
		cerr << "Unexpected Error Occured" << endl;
		exitcode = 1;
	}
	return exitcode;
}
