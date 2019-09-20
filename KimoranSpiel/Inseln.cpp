#include "Inseln.h"
#include <iostream>

using namespace std;

bool Inseln::get_schatz() {
	return m_schatz;
}
void Inseln::set_schatz(bool schatz) {
	m_schatz = schatz;
}
double Inseln::get_taler() {
	return m_taler;
}
void Inseln::set_taler(double taler) {
	m_taler = taler;
}
