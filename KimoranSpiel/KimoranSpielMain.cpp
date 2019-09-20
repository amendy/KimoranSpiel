
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include "Graph.h"
#include "GUI.h"



using namespace std;

//Zuerst einmal die bidirectionale Verbindung herstellen
//prendre un pointeur de Graph commencant de la source á la destination
// et cela avec les informations supplémentaires

int main()
{


	GUI gui; // GUI aufrufen

	bool bRunning = true;

	// Endlosschleife, bis bRunning auf 'false' gesetzt wird
	while (bRunning)
	{
		int menuEntry = gui.showMenu();

		// Hinweis: Die Fallunterscheidung geht auch mit Switch-Case (siehe C-Programmierung)



		switch (menuEntry)
		{
		case 1:
			gui.readData("C23_Projekt_19SS_Inseln.txt");
			break;
		case 2:
			gui.AusgabeAlsjpg();
			break;
		case 3:
			gui.neueZielInseln();
			break;
		case 4:
			gui.computerRandomSpiel();
			break;
		case 5:
			bRunning = false;
			break;

		default:
			break;
		}




	}
	system("pause");
	return 0;

}