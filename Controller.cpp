#include "Core.hpp"
#include <iostream>
using namespace std;

int main()
{
	Initialize();

Start:

	// input state
	int8 State[StateLen];
	cout << "State (6 blocks): ";
	for (int8 i = 0; i < StateLen; i++)
	{
		int state;
		cin >> state;
		State[i] = state;
	}

	// solve
	int8 *path = Search(State);
	if (path == nullptr) cout << "wrong" << endl;
	else
	{
		cout << "nStep: " << (int)path[GodNum] << endl;
		cout << "path: ";
		for (int8 i = 0; i < path[GodNum]; i++)
			cout << (int)path[i] << ' ';
	}

	cout << endl << endl;
	goto Start;

	system("pause");
}