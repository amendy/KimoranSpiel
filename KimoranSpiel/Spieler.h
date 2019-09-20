#pragma once
#include "Inseln.h"

class Spieler {
public:
	Spieler(int type, Inseln* position, double taler) : m_type(type), m_position(position), m_taler(taler) {};
	Spieler() { m_position = new Inseln(); };


	void setPosition(Inseln newPosition) { this->m_position = &newPosition; };
	Inseln& getPosition() { return *m_position; };
	int getType() { return m_type; };
	void setTaler(double newTaler) { this->m_taler = newTaler; };
	double getTaler() { return m_taler; };



private:
	int m_type;
	Inseln* m_position;
	double m_taler;
};
