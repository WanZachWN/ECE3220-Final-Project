#include "minesweeper.h"

int main()
{
	Minesweeper *mine = new Minesweeper();
	int x = 0;
	int y = 0;
	char cont;
	
	while (true)
	{
		cout << "Would you like to start a new game or load?" << endl
			<< "n = new game" << endl
			<< "l = load game" << endl;
		cin >> cont;

		if (cont == 'n') //load exist
		{
			mine->GenerateMap();
			break;
		}
		else if (cont == 'l')
		{
			cout << "Loading from a saved game..." << endl;
			
			if (!mine->io->Load(*mine->map)) //load exist
			{
				cout << "Starting new game..." << endl;
				mine->GenerateMap();;
			}
			break;
		}
		else
		{
			cout << "Invalid character entry!" << endl;
		}
	}

	try {

		Print(*mine->map);
		while (true)
		{
			while (true)
			{
				cout << "Enter Row: ";
				cin >> x;
				cout << "Enter Column: ";
				cin >> y;
				if (x > 0 && x <= mine->map->ROW) 
				{
					if (y > 0 && y <= mine->map->COL)
					{
						break;
					}
				}
				else
				{
					cout << "Invalid coordinates, exceeds boundaries!" << endl;
				}
			}
			
			mine->Check(x - 1, y - 1);
			if (GetLose(*mine))
			{
				Print(*mine->map);
				cout << "You Lose!" << endl;
				break;
			}
			else if (GetWin(*mine))
			{
				Print(*mine->map);
				cout << "You Win!" << endl;
				mine->io->Delete();
				break;
			}
			Print(*mine->map);
			cout << "Would you like to continue? (y/n): ";
			cin >> cont;

			if (cont == 'n')
			{
				mine->io->Save(*mine->map);
				break;
			}
		}
	}
	catch (...)
	{
		cerr << "Unexpected Error Occured" << endl;
	}
	return 0;
}
