#include "GUI.h"
#include <iostream>
#include <deque>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include "Graph.h"
#include "Inseln.h"
#include "Spieler.h"
#include "Connection.h"
#include <ctime>

using namespace std;

int GUI::showMenu() {

	std::cout << "Bitte waehlen Sie eine Zahl für die jeweilige Aktion:" << std::endl
		<< "1 - Einlesen der Kimoran-Welt aus einer Datei" << std::endl
		<< "2 - Ausgeben der Welt graphisch oder textuell" << std::endl
		<< "3 - Eingeben der Zielinsel für den nächsten Spielzug des menschlichen Spielers \nBerechnen der kostenoptimalen Verbindung zur Zielinsel \nAusführen und Ausgeben der Verbindung zur Zielinsel\nEinsammeln aller Taler aus geheimen Lagern \nSuchen des Schatzes auf der Zielinsel, Spielzug beenden" << std::endl
		<< "4 - Auswaehlen der Zielinsel für den nächsten Spielzug des Computer-Spielers" << std::endl
		<< "5 - Beenden" << std::endl;


	std::cout << "Eingabe: ";
	int eingabe;
	std::cin >> eingabe;
	return eingabe;
}

Node* GUI::getZielInsel() {
	// Inseln ist ein Node, wie bekomme ich ein Node?
	
	// Node it ein String über die Nodeid. 
	
	std::string nodeId; // Deklaration

	Node* pNode = NULL; // Node Initialisieren
	
	/*do{} while(); return */

	do {
		std::cout << "Bitte Zielinseln angeben: ";
		std::cin >> nodeId;

		pNode = this->findNode(nodeId);

		if (pNode == NULL) {
			std::cout << "Node nicht gefunden!" << std::endl;
		}

	} while (pNode == NULL);

	return pNode; 
}
// Einlesen der Kimoran-Welt aus einer Datei
// Datei einlesen und als String ausgeben und speichern in einer Art. 
void GUI::readData(const std::string& rFilename) {
	ifstream inFile; //Input File Stream Object gebaut
	try
	{
		inFile.open(rFilename);
		if (!inFile.good()) {
			cout << "File koennte nicht geoffnet werden" << endl;
			return;
			// 
		}
		else
		{
			cout << "Datei geoffnet " << endl;
			/* readData mit einem try{} catch(){}- Anweisungen
			try {
			inFile.open(rFilename); //Variable Initialisieren
			// Die Methode heißt inFile.good d.h wenn es klappt, dass die Datei geöffnet wird
			if(!inFile.good()){
			std::cout <<"File nicht geoffnet"<< std::endl;
			return; 
			}
			else{
			std::cout << " Datei geoeffnet" << std::endl; 
			}
			}
			catch( const ifstream::failure& e){
			std:: cout << "e.what()" << std::endl; 
			}
			*/
			// Ein leeres String wird erzeugt und der Counter hilft die anzahl zu zaehlen. 
			
			string zeile = "";
			int counter = 0;
			int counterschatz = 0;
			int countertunnel = 0;
			int counterbruecke = 0;
			int counterfaehre = 0;
			while (getline(inFile, zeile))
			{
				istringstream iss(zeile); // Deswegen sstream included
				vector<string> tokens{ istream_iterator<string>{iss},
					  istream_iterator<string>{} };

				if (tokens[0] == "Insel")
				{
					this->addNode(new Inseln(tokens[1], false, 0));
					counter++;
				}
				if (tokens[0] == "Tunnel")
				{
					this->addEdge(new Connection(*(this->findNode(tokens[1])), *(this->findNode(tokens[2])), 5, 1));
					this->addEdge(new Connection(*(this->findNode(tokens[2])), *(this->findNode(tokens[1])), 5, 1));
					countertunnel++;
				}
				if (tokens[0] == "Bruecke")
				{
					this->addEdge(new Connection(*(this->findNode(tokens[1])), *(this->findNode(tokens[2])), 3, 2));
					this->addEdge(new Connection(*(this->findNode(tokens[2])), *(this->findNode(tokens[1])), 3, 2));
					counterbruecke++;
				}
				if (tokens[0] == "Faehre")
				{
					this->addEdge(new Connection(*(this->findNode(tokens[1])), *(this->findNode(tokens[2])), 3, 3));
					this->addEdge(new Connection(*(this->findNode(tokens[2])), *(this->findNode(tokens[1])), 3, 3));

					counterfaehre++;
				}
					if (tokens[0] == "Schatz")
					{
						Node* node = this->findNode(tokens[1]);
						Inseln& temp = static_cast<Inseln&>(*node);
						if (temp.getID() != "")
						{
							temp.set_schatz(true);
						}
						counterschatz++;
					}
					if (tokens[0] == "Lager")
					{
						Node* node = this->findNode(tokens[1]);
						Inseln& temp = static_cast<Inseln&>(*node);
						if (temp.getID() != "")
						{
							temp.set_taler(std::stod(tokens[2]));
						}
					}
					if (tokens[0] == "Mensch")
					{
						this->addspieler(new Spieler(1, static_cast<Inseln*>(this->findNode(tokens[1])), std::stod(tokens[2])));
					}
					if (tokens[0] == "Computer")
					{
						this->addspieler(new Spieler(2, static_cast<Inseln*>(this->findNode(tokens[1])), std::stod(tokens[2])));
					}

					//cout << tokens[0] << endl;
				
			}

				cout << "Counter Insel = " << counter << endl;
				cout << "Counter Tunnel  = " << countertunnel << endl;
				cout << "Counter Bruecke  = " << counterbruecke << endl;
				cout << "Counter Faehre = " << counterfaehre << endl;
				cout << "Counter Schatz = " << counterschatz << endl;

				inFile.close();
			
		}

	}
	catch (const ifstream::failure& e)
	{
		cout << e.what() << endl;
	}



}
// Ein Spieler hinzufügen
// Vector benutzen und Elemente hinzuzufügen

void GUI::addspieler(Spieler* spieler)
{
	m_spieler.push_back(spieler);
}
// Datei in einer graphische Darstellung

void GUI::saveAsDot(const std::string& rFilename)
{
	/*
	Kopieren Sie den Ordner ‚Peters\C23_Algorithmen_Programmierung\Tools\graphviz‘ im Dozentenserver auf ein lokales Laufwerk.

	Graphiz ist ein Tool, welches Graphen aus einer textuellen Beschreibung erzeugen kann.
	Betrachten Sie die Datei graph.dot.
	Formal ist die Datei folgendermaßen aufgebaut :

	digraph {
	concentrate = true
	<NODE_ID>;
	<NODE_ID>;
	<NODE_ID>;
	<EDGE_1>;
	<EDGE_2>;
	<EDGE_N>;
	}

	Starten Sie die Datei make.bat, damit Graphiz ein Bild des Graphen erstellt.
	Spielen Sie mit der Datei graph.dot herum und lassen Sie sich den Graph dazu generieren.


	Implementieren Sie nun die Funktion 'Graph::saveAsDot', damit sie eine Dot-Datei im angegebenen Dateipfad erzeugt!

	Hilfestellung:
	- Dateien speichern mit C++: http://www.cplusplus.com/reference/fstream/fstream/open/
	- Verwenden Sie die Funktionen Node::getID() und Edge::toString(), um die Einträge für die Nodes und Edges in der dot - Datei zu generieren.


	TEST:
	Testen Sie die Funktion, indem Sie indem Sie einen Graph in mit ein paar Nodes und Edges in main.cpp erstellen
	und anschließend eine dot-Datei generieren. Erstellen Sie ein Bild des Graphen mit Graphviz.

	*/
	std::fstream fs;
	fs.open(rFilename, std::fstream::out | std::fstream::trunc);
	fs << "digraph {" << std::endl;
	fs << "concentrate=true" << std::endl;
	for (auto temp : m_nodes) {
		fs << "\"" << temp->getID() << "\"" << ";" << std::endl;
	}
	for (auto temp : m_edges) {
		Inseln* t = dynamic_cast<Inseln*>(temp);
		fs << "\"" << temp->getSrcNode().getID() << "\"" << " -> " << "\"" << temp->getDstNode().getID() << "\" " << " [label=\"" << temp->getWeight() << "\" " << "dir=both color=\"#" << "ff0000" << "\" " << "];" << std::endl;
	}
	fs << "}" << std::endl;
	fs.close();
}





void executeBatch(const char* BatchFile) {
	system(BatchFile);
}
// Datei graphisch als jpg speichern 

bool GUI:: AusgabeAlsjpg() {
	try {
		this->saveAsDot("graph.dot");
		executeBatch("make.bat");
		system("out.png");
		return true;
	}
	catch (std::exception e)
	{
		cout << e.what() << endl;
		return false;
	}
}
// Eingabe der Zielinsel 

bool GUI:: neueZielInseln()
{
	for (Node* var : m_nodes)
	{
		cout << var->getID() << endl;
	}

	Node* ziel = this->getZielInsel();

	this->optimaleVerbindung(*ziel, 1);


	Inseln spielerPosition; // for the case Default Constructor should be created on Inseln
	for (Spieler *temp : m_spieler) {
		if (temp->getType() == 1) {
			//temp->getPosition(); 
			spielerPosition = temp->getPosition();
		}
	}
	for (auto edgeTemp : spielerPosition.getOutEdges()) {
		cout << "Nachbarn sind " << edgeTemp->getDstNode().getID() << endl;

	}

	return true;

}

// Berechnen der kosten-optimalen Verbindung zur Zielinsel

void GUI:: optimaleVerbindung(Node ziel, int spielerType)
{
	std::deque<Edge*>*rPath = new std::deque<Edge*>();
	Node spielerPosition; // for the case Default Constructor should be created on Inseln
	Spieler* mensch = new Spieler();
	for (Spieler *temp : m_spieler) {
		if (temp->getType() == spielerType) {
			//temp->getPosition(); 
			spielerPosition = temp->getPosition();
			mensch = temp;
		}
	}

	double summe = 0;
	this->findShortestPathDijkstra(*rPath, spielerPosition, ziel);
	for (auto edge : *rPath) 
	{
		summe = edge->getWeight();
		cout << "Source Inseln :" << edge->getSrcNode().getID() << " Zur Inseln : " << edge->getDstNode().getID() << endl;
		Inseln* weg = static_cast<Inseln*>(&(edge->getDstNode()));
		if (weg->get_schatz() == true)
		{
			cout << "you are winner" << endl;
			mensch->setPosition(static_cast<Inseln&>(ziel));
			system("pause");
			std::exit(0);
			// End the programm
		}
		if (weg->get_taler() > 0) {
			mensch->setTaler(weg->get_taler() + mensch->getTaler());
		}
		if (typeid(*edge).name() == "Bruecke")
		{
			Connection* temp = dynamic_cast<Connection*>(edge);
		}
		if (typeid(*edge).name() == "Faehre")
		{
			Connection* temp = dynamic_cast<Connection*>(edge);

		}
		if (typeid(*edge).name() == "Tunnel")
		{
			Connection* temp = dynamic_cast<Connection*>(edge);
		}
	}
	if (summe > mensch->getTaler())
	{
		cout << "you loosed the game" << endl;
		
	}
	else
	{
		mensch->setTaler(mensch->getTaler() - summe);

		mensch->setPosition(static_cast<Inseln&>(ziel));
	}
	this->computerRandomSpiel();

}
// der Computer-Spieler ist dran

bool  GUI:: computerRandomSpiel()
{
	Node *ziel = new Node();
	int n = m_nodes.size();
	int dice = (rand() % n) + 1;
	// Create iterator pointing to first element
	std::list<Node*>::iterator it = m_nodes.begin();

	// Advance the iterator by 2 positions,
	std::advance(it, dice);
	ziel = *it;
	this->optimaleVerbindung(*ziel, 2);


	Inseln spielerPosition; // for the case Default Constructor should be created on Inseln
	for (Spieler *temp : m_spieler) 
	{
		if (temp->getType() == 2) {
			//temp->getPosition(); 
			spielerPosition = temp->getPosition();
		}
	}
	for (auto edgeTemp : spielerPosition.getOutEdges()) {
		cout << "Nachbarn sind " << edgeTemp->getDstNode().getID() << endl;

	}

	this->optimaleVerbindung(*ziel, 2);


	//	Inseln spielerPosition; // for the case Default Constructor should be created on Inseln
	for (Spieler *temp : m_spieler) {
		if (temp->getType() == 1) {
			//temp->getPosition(); 
			spielerPosition = temp->getPosition();
		}
	}
	for (auto edgeTemp : spielerPosition.getOutEdges()) {
		cout << "Nachbarn sind " << edgeTemp->getDstNode().getID() << endl;

	}


	return true;
}
