#pragma once
#include "Edge.h"
#include <iostream>

using namespace std;


class Connection : public Edge
{

public:
	// Construktor Connection bauen mit zusaeztlichen Informationen bauen
	Connection(Node &rSrc, Node &rDes, double kost, int type) : Edge(rSrc, rDes),
		m_kost(kost), m_type(type)
	{
		// we have to define what is Type and what will be done. 
		// This can only be done here
		if (type == 1)
		{
			m_typeName = "Tunnel";
			m_kost = 5;
		}
		else if (type == 2)
		{
			m_typeName = "Bruecke";
			m_kost = 3;
		}
		else if (type == 3)
		{
			m_typeName = "Faehre";
			m_kost = 3;
		}
		

	}
	virtual double getWeight()
	{
			return  m_kost;
	
	}
	double getkost() { return m_kost; }
	int getType() { return m_type; }
	double getKost() { return m_kost; }
	string getTypeName() { return m_typeName; }

private:
	double m_kost;
	int m_type;
	string m_typeName;

};

