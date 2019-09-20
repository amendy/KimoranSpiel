#pragma once
#include "Graph.h"
#include "Spieler.h"

class GUI : public Graph
{
public:
	// Hier die Funktionen

	int showMenu();
	Node* getZielInsel();
	void readData(const std::string& rFilename);
	void addspieler(Spieler* spieler);
	bool AusgabeAlsjpg();
	void saveAsDot(const std::string& rFilename);
	bool neueZielInseln();
	void optimaleVerbindung(Node ziel, int spielerType);
	bool computerRandomSpiel();


private:
	std::list<Spieler*> m_spieler;
};

class GUIException
{

public:

	GUIException(const std::string& msg) : m_msg(msg) {}

	std::string getError() const { return m_msg; }


private:

	std::string m_msg;

};




