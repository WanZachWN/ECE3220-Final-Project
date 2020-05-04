#include "minesweeper.h"

int main()
{
	Minesweeper *mine = new Minesweeper();
	bool lose = false;
	int x = 0;
	int y = 0;
	

	while (true)
	{
		mine->Print();
		cout << "Enter row: ";
		cin >> x;
		cout << "Enter column: ";
		cin >> y;

		lose = mine->Check(x-1, y-1);
		if (lose == true)
		{
			mine->Print();
			cout << "You Lose!" << endl;
			break;
		}
	}

	return 0;
}
