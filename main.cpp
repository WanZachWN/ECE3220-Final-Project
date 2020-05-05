#include "minesweeper.h"

int main()
{
	Minesweeper *mine = new Minesweeper();
	int x = 0;
	int y = 0;
	char cont;

	try {
		Print(*mine);
		while (true)
		{
			cout << "Enter Row: ";
			cin >> x;
			cout << "Enter Columns: ";
			cin >> y;

			mine->Check(x - 1, y - 1);
			if (GetLose(*mine) == true)
			{
				Print(*mine);
				cout << "You Lose!" << endl;
				break;
			}
			else if (GetWin(*mine) == true)
			{
				Print(*mine);
				cout << "You Win!" << endl;
			}
			Print(*mine);
			cout << "Would you like to continue? (y/n): ";
			cin >> cont;

			if (cont == 'n')
			{
				mine->Save();
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
