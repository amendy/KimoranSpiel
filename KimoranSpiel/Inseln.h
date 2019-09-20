#pragma once
#include "Node.h"
#include <iostream>

using namespace std; 

class Inseln : public Node
{
public:
	//Constructor
	Inseln(std::string id, bool schatz, double taler) : Node(id),
		m_schatz(schatz), m_taler(taler) {};
	// Default Constructor
	Inseln() {

	};
	bool get_schatz();
	void set_schatz(bool schatz);
	double get_taler();
	void set_taler(double taler);


private:
	bool m_schatz;
	double m_taler;

};

