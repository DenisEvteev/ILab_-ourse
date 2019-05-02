#include "Classes_With_Methods.h"
//-------------------------------------------------------------------------------------
int main()
{
	SetConsoleCP(1251);     // installation code page win-cp 1251 in the input stream
	SetConsoleOutputCP(1251); // setting the code page win-cp 1251 to the output stream
	

	setlocale(LC_ALL, "rus");

	Game_Manager* GM = new Game_Manager;

	GM->Menu_For_Acinator();



	delete GM;
	system("pause");
	return 0;
}